#include "huffman.h"

void decode_hcode(char *fname, char *buff, t_node *tree_head, uint32_t ucomp_len)
{
	t_node *curr_posi_tree;
	uint32_t start;
	char *str;
	uint32_t j;

	str = (char*)malloc(ucomp_len + 1);
	start = 0;
	curr_posi_tree = tree_head;
	j = 0;
	while (j < ucomp_len)
	{
		if (read_bits(buff, &start, 1) == 1 && curr_posi_tree->right != NULL)
			curr_posi_tree = curr_posi_tree->right;
		else if (curr_posi_tree->left != NULL)
			curr_posi_tree = curr_posi_tree->left;
		if (curr_posi_tree->k == e_leaf)
		{
			str[j++] = curr_posi_tree->c;
			curr_posi_tree = tree_head;
		}
	}
	write_to_file(get_fname_noext(fname), str, ucomp_len);
}

/*
 * : on how to decode tree from https://engineering.purdue.edu/ece264/20au/hw/HW12?alt=huffman
 * To construct a Huffman coding tree from the header information, we make use of a stack. When a 1 
 * (bit or character depending on whether we are dealing with a bit-based or character-based representation) is read,
 * we read the next byte and push the corresponding ASCII character onto the stack. When a 0 (bit or character) is read,
 * if the stack contains only one element, we have constructed the entire Huffman coding tree. 
 * Otherwise, there must be more than one element in the stack. We create a new node, and pop the top two elements off the stack. 
 * We make the first element off the stack the right child of the new node,
 * and the second element off the stack the left child of the new node. 
 * After that, we push the newly created node onto the stack.
 */

t_node	*decode_tree(char *buff, uint32_t *start, uint32_t tree_len)
{
	t_list *stack;
	t_list *left;
	t_list *right;
	int bit;
	t_node *tree_head;

	stack = NULL;
	while (*start < (3 * sizeof(uint32_t) + tree_len) * 8)//3bytes * 8 bits
	{
		bit = read_bits(buff, start, 1);
		if (bit == 1)
			lstadd(&stack, creat_node(read_bits(buff, start, 8), 0, e_leaf, NULL, NULL));
		else if (bit == 0 && lstlen(stack) > 1)
		{
			right = lstpop(&stack);
			left = lstpop(&stack);
			lstadd(&stack, creat_node(0, 0, e_nonleaf, (t_node*)left->content, (t_node*)right->content));
			free(left);
			free(right);
		}
	}
	tree_head = (t_node*)stack->content;
	free(stack);
	return (tree_head);
}

void decode(int fd, char *fname, int fsize)
{
	uint32_t start;
	uint32_t comp_len;
	uint32_t tree_len;
	uint32_t ucomp_len;
	t_node *tree_head;
	char *buff;

	start = 0;
	buff = malloc(fsize);
	read(fd, buff, fsize);
	comp_len = read_bits(buff, &start, sizeof(uint32_t) * 8);
	tree_len = read_bits(buff, &start, sizeof(uint32_t) * 8);
	ucomp_len = read_bits(buff, &start, sizeof(uint32_t) * 8);
	tree_head = decode_tree(buff, &start, tree_len);
	decode_hcode(fname, buff + (start / 8), tree_head, ucomp_len);//offset buff to start of hcode
	/*print_bits(buff + (start / 8), comp_len - ((3 * sizeof(uint32_t)) + tree_len)); */
	(void)comp_len;
	free(buff);
	tree_free(tree_head);
	printf("successfully decoded!👌\n");
}
