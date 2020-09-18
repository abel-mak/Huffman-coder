#include "huffman.h"

void huff_code_print(signed int n, int bits_len)
{
	int i;
	int bit;

	i = (bits_len > 0) ? bits_len - 1 : 0;
	while (i >= 0)
	{
		bit = (n >> i) & 1;
		printf("%d", bit);
		i--;
	}
	putchar('\n');
}

void print_bits(char *arr, uint32_t len)
{
	uint32_t i;
	int x;
	int y;

	i = 0;
	while (i < len * 8)
	{
		if (i % 8 == 0 && i != 0)
			putchar('\n');
		x = i % 8;
		y = (i / 8); 
		printf("%d", ((int)arr[y] >> abs(x - 7)) & 1);
		i++;
	}
	putchar('\n');
}

void print_huff_table(t_list *huff_table)
{
	t_list *tmp;
	t_huff_code *hcode;

	tmp = huff_table;
	while (tmp)
	{
		hcode = tmp->content;
		printf("|%d|%c|", hcode->len, hcode->c);
		huff_code_print(hcode->code, hcode->len);
		tmp = tmp->next;
	}
}

void print_freq(t_node **arr_nodes)
{
	int i;

	i = 0;	
	while (arr_nodes[i] != NULL)
	{
		printf("%c: %d\n", arr_nodes[i]->c, arr_nodes[i]->freq);
		i++;
	}
}
