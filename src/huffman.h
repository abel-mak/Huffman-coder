
#ifndef HUFFMAN_H
# define HUFFMAN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef unsigned int uint32_t;

enum    e_kind
{
	e_leaf,
	e_nonleaf
};

typedef struct  s_node
{
	char            c;
	int             freq;
	enum e_kind     k;
	struct s_node   *left;
	struct s_node   *right;
}		t_node;

typedef struct	s_list
{
	void *content;
	struct s_list *next;
}		t_list;

typedef struct s_huff_code
{
	        char c;
		        signed int code;
			        int len;
}               t_huff_code;

t_list		*lstnew(void *content);
t_list		*lstadd(t_list **head, void *content);
t_list		*lstpop(t_list **head);
void		lstfree(t_list *head);
uint32_t	lstlen(t_list *head);
t_node		*creat_node(char c, int freq, enum e_kind k, t_node *left, t_node *right);
void		get_freq_str(int *arr, char *str);
int		get_arr_nodes_len(int *freq_arr);
t_node		**get_arr_nodes(char *str);
void 		sort_arr_nodes(t_node **arr_nodes);
void		build_tree(t_node **arr_nodes);
void		huff_code_print(signed int n, int bits_len);
void		build_huff_table(t_node *root, signed int code, int current, uint32_t *tree_len, t_list **huff_table);
void		encode_tree_buff(t_node *root, char *buff, uint32_t *start);
void		tree_free(t_node *root);
int		write_bits(char *arr, uint32_t start, int input, int input_len);
void		print_bits(char *arr, uint32_t len);
uint32_t	get_total_hcode_len(char *str, t_list *huff_table);
int		encode_header_buff(t_node *root, char *buff, uint32_t tree_len, uint32_t comp_len, uint32_t ucomp_len);
int		encode_hcode_buff(t_list *huff_table, char *buff, char *str, uint32_t start);
uint32_t	read_bits(char *buff, uint32_t *start, int bits_len);
int		end_with(char *s1, char *suffix);
char		*get_fname_noext(char *fname);
void		write_to_file(char *fname, char *buff, uint32_t buff_len);
void		decode_hcode(char *fname, char *buff, t_node *tree_head, uint32_t ucomp_len);
t_node		*decode_tree(char *buff, uint32_t *start, uint32_t tree_len);
void		decode(int fd, char *fname, int fsize);
char		*strjoin(char *dest, char *s1, char *s2);
void		encode_hcode_file(char *fname, t_node *root, uint32_t tree_len, char *str, t_list *huff_table);
void		print_huff_table(t_list *huff_table);
void		print_freq(t_node **arr_nodes);
void		encode(int fd, char *fname, int fsize);

#endif
