#include "huffman.h"

void get_freq_str(int *arr, char *str)
{
	int i;

	memset(arr, 0, sizeof(int) * 256);
	i = 0;
	while (str[i] != '\0')
	{
		arr[(unsigned char)str[i]]++;
		i++;
	}
}

uint32_t get_total_hcode_len(char *str, t_list *huff_table)
{
	uint32_t i;
	uint32_t len;
	t_list *tmp;
	t_huff_code *hcode;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		tmp = huff_table;
		while (tmp)
		{
			hcode = (t_huff_code*)tmp->content;
			if (str[i] == hcode->c)
				len += hcode->len;
			tmp = tmp->next;
		}
		i++;
	}
	return (len);
}

int end_with(char *s1, char *suffix)
{
	uint32_t i;
	uint32_t j;

	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		while (s1[i + j] == suffix[j] && j < strlen(suffix))
			j++;
		if (j == strlen(suffix) && (i + j) == strlen(s1))
			return (1);
		i++;
	}
	return (0);
}

/* 
 * get fname without file extension
 */

char *get_fname_noext(char *fname)
{
	char *ext;
	uint32_t i;
	uint32_t j;

	ext = ".huff";
	i = 0;
	while (fname[i] != '\0')
	{
		j = 0;
		while(fname[i + j] == ext[j] && j < strlen(ext))
			j++;
		if (j == strlen(ext) && (i + j) == strlen(fname))
		{
			fname[i] = '\0';
			return (fname);
		}
		i++;
	}
	return (fname);
}

char *strjoin(char *dest, char *s1, char *s2)
{
	strcpy(dest, s1);
	strcat(dest, s2);
	return (dest);
}
