#include "huffman.h"

/*
 *  build_tree get as argument array of nodes call sort_arr_nodes to sort from high to least frequency
 *	take the two last elements of the array  and create subtree (which is just a node with not null left and right childs)
 *	then push the tree at last of the array then sort and repeat 
 *	until there's only one element (length of array == 1)
 */

void build_tree(t_node **arr_nodes)
{
	int i;
	int tmp_freq;

	sort_arr_nodes(arr_nodes);
	i = 0;
	while (arr_nodes[i] != NULL)
		i++;
	if (i > 1)
	{
		tmp_freq = arr_nodes[i - 2]->freq + arr_nodes[i - 1]->freq;
		arr_nodes[i - 2] = creat_node(0, tmp_freq, e_nonleaf, arr_nodes[i - 1], arr_nodes[i - 2]);
		arr_nodes[i - 1] = NULL;
		build_tree(arr_nodes);
	}
}


/*
 *  the function calculate the length of tree and generate huffman table
 */

void  build_huff_table(t_node *root, signed int code, int current, uint32_t *tree_len, t_list **huff_table)
{
	t_huff_code *hcode;

	if (root->k == e_leaf)
		*tree_len += 9;
	else
		*tree_len += 1;
	if (root->right != NULL)
		build_huff_table(root->right, (code << 1) | 1, current + 1, tree_len, huff_table);
	if (root->left != NULL)
		build_huff_table(root->left, (code << 1) & ~(1), current + 1, tree_len, huff_table);
	if (root->k == e_leaf)
	{
		hcode = (t_huff_code*)malloc(sizeof(t_huff_code));//freed
		hcode->c = root->c;
		hcode->code = code;
		hcode->len = (current != 0) ? current : 1;
		lstadd(huff_table, hcode);
	}
}


void tree_free(t_node *root)
{
	if (root->left != NULL)
		tree_free(root->left);
	if (root->right != NULL)
		tree_free(root->right);
	free(root);
}
/*
 * : how post-order traversing work from wikipedia:
 * Traverse the left subtree by recursively calling the post-order function.
 * Traverse the right subtree by recursively calling the post-order function.
 * Access the data part of the current node.
 */

/*
 * : I used start variable adress because the function is recursive so it will mess up
 * start variable and for that i used the adress to directly modify it keep track of where 
 * we are at the tree array 
 */

/*
 *post order will store tree to buff in post order
 */

void encode_tree_buff(t_node *root, char *buff, uint32_t *start)
{	
	if (root->left != NULL)
		encode_tree_buff(root->left, buff, start);
	if (root->right != NULL)
		encode_tree_buff(root->right, buff, start);
	if (root->k == e_leaf)
	{
		*start = write_bits(buff, *start, 1, 1);
		*start = write_bits(buff, *start, root->c, sizeof(char) * 8);
	}
	else
		*start = write_bits(buff, *start, 0, 1);
}

/* 
 * encode_header_buff after poste_order store the tree write 0 at the end of tree to mark the end of tree
 */

int encode_header_buff(t_node *root, char *buff, uint32_t tree_len, uint32_t comp_len, uint32_t ucomp_len)
{
	uint32_t start;

	start = 0;
	start = write_bits(buff, start, comp_len, sizeof(uint32_t) * 8);
	start = write_bits(buff, start, tree_len, sizeof(uint32_t) * 8);
	start = write_bits(buff, start, ucomp_len, sizeof(uint32_t) * 8);
	encode_tree_buff(root, buff, &start);
	putchar('\n');
	start = write_bits(buff, start, 0, 1); 
	return (start);
}

/* 
 * loop through huff_table if we find a character equal to str[i] write the code of the character
 */

int  encode_hcode_buff(t_list *huff_table, char *buff, char *str, uint32_t start)
{
	int		i;
	t_list 		*tmp;
	t_huff_code	*hcode;

	i = 0;
	while (str[i] != 0)
	{
		tmp = huff_table;
		while (tmp != NULL)
		{
			hcode = tmp->content;
			if (hcode->c == str[i])
			{
				start = write_bits(buff, start, hcode->code, hcode->len);
				break;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (start);
}

/* 
 * comp_len The total number of characters in the compressed file
 * ucomp_len The total number of characters in the original uncompressed file
 * after encode_header_buff  move start to the next byte after writing the header and
 * start writing huff code from next byte
 */

void encode_hcode_file(char *fname, t_node *root, uint32_t tree_len, char *str, t_list *huff_table)
{
	char *buff;
	uint32_t comp_len;
	uint32_t ucomp_len;
	uint32_t start;
	char cmp_fname[strlen(fname) + strlen(".huff") + 1];

	comp_len = tree_len 
		+ (uint32_t)ceil((get_total_hcode_len(str, huff_table) / 8.))
		+ (3 * sizeof(uint32_t));
	ucomp_len = strlen(str);
	buff = (char*)malloc(comp_len);
	memset(buff, 0, comp_len);
	printf("comp: %d byte\n", comp_len);
	printf("tree_len: %d byte\n", tree_len);
	printf("ucomp: %d byte\n", ucomp_len);
	start = encode_header_buff(root, buff, tree_len, comp_len, ucomp_len);
	start += (start % 8 == 0) ? 0 : (8 - (start % 8)); 
	start = encode_hcode_buff(huff_table, buff, str, start);
	/*	printf("\nfile buff:\n"); */
	/*	print_bits(buff, comp_len);*/
	write_to_file(strjoin(cmp_fname, fname, ".huff"), buff, comp_len);
}

/* 
 * tree_len is how much bits needed to store the huffman tree in post order
 * build_huff_table return tree_len in bits so i convert it to bytes
 * 1 is added to tree_len for last bit 0 that tell we reached the end of tree
 */

void encode(int fd, char *fname, int fsize)
{
	char *str;
	uint32_t tree_len;
	t_node **arr_nodes;
	t_list *huff_table;

	huff_table = NULL;
	tree_len = 0;
	str = malloc(fsize + 1);
	read(fd, str, fsize);
	str[fsize] = '\0';
	arr_nodes = get_arr_nodes(str);
	print_freq(arr_nodes);
	build_tree(arr_nodes);
	build_huff_table(arr_nodes[0], 0, 0, &tree_len, &huff_table);
	tree_len = (uint32_t)ceil((tree_len + 1.) / 8);
	print_huff_table(huff_table);
	encode_hcode_file(fname, arr_nodes[0], tree_len, str, huff_table);
	tree_free(arr_nodes[0]);
	lstfree(huff_table);
	free(arr_nodes);
	free(str);	
	printf("successfully encoded!👌\n");
}
