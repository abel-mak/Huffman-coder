#include "huffman.h"

t_node *creat_node(char c, int freq, enum e_kind k, t_node *left, t_node *right)
{
	t_node *node;

	node = (t_node*)malloc(sizeof(t_node));
	node->c = c;
	node->freq = freq;
	node->k = k;
	node->left = left;
	node->right = right;
	return (node);
}

int get_arr_nodes_len(int *freq_arr)
{
	uint32_t i;
	int res;

	res = 0;
	i = 0;
	while (i < 256)
	{
		if (freq_arr[i] != 0)
			res++;
		i++;
	}
	return (res);
}

t_node **get_arr_nodes(char *str)
{
	int i;
	int j;
	int arr_nodes_len; //array of nodes
	t_node **res;
	int freq_arr[256];


	get_freq_str(freq_arr, str);
	arr_nodes_len = get_arr_nodes_len(freq_arr);
	res = (t_node**)malloc(sizeof(t_node*) * (arr_nodes_len + 1));//freed
	j = 0;
	i = 0;
	while (i < 256)
	{
		if (freq_arr[i] != 0)
		{
			res[j] = creat_node((char)i, freq_arr[i], e_leaf, NULL, NULL);	
			j++;
		}
		i++;
	}
	res[j] = NULL;
	return (res);
}

/* 
 * for second condition (equal frequencies) sort give priority (for swiping to right) 
 * to node with leaf over node without and have childs which mean more bits
 * before (2, c) (2, d)(2, (a,b)) 
 * non optimal subtree (2, c) (4, ((d, (a, b)))) then (6, (c, (d, (a, b))) depth equal 3
 * optimal (2, (a, b)) (4, (c, d)) then (6, ((a, b), (c, d))) depth 2
 * the less depth less bits
 */

void sort_arr_nodes(t_node **arr_nodes)
{
	int i;
	t_node *tmp;

	i = 1;
	while (arr_nodes[i] != NULL && arr_nodes[1] != NULL)
	{
		if (arr_nodes[i - 1]->freq < arr_nodes[i]->freq || 
				((arr_nodes[i - 1]->freq == arr_nodes[i]->freq) && (arr_nodes[i - 1]->k == e_leaf
					&& arr_nodes[i]->k == e_nonleaf)))
		{
			tmp = arr_nodes[i - 1];
			arr_nodes[i - 1] = arr_nodes[i];
			arr_nodes[i] = tmp;
			i = 1;
		}
		else
			i++;
	}
}
