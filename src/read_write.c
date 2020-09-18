#include "huffman.h"

/* 
 * write_bits will write input_len bits from input to start bit in arr 
 */

int  write_bits(char *dest, uint32_t start, int input, int input_len)
{
	int j;
	uint32_t i;
	int x;
	int y;
	char mask[8] = {1 << 7, 1 << 6, 1 << 5, 1 << 4, 1 << 3, 1 << 2, 1 << 1, 1};

	i = start;
	j = input_len - 1; // to shift 
	while (i < start + input_len)
	{
		x = i % 8;
		y = (i / 8);
		dest[y] = (((input >> j) & 1) == 1) ? dest[y] | mask[x] : dest[y] & ~mask[x];
		j--;
		i++;
	}
	return (i);
}

uint32_t read_bits(char *buff, uint32_t *start, int bits_len)
{
	int i;
	int x;
	int y;
	uint32_t res;

	res = 0;
	i = bits_len - 1;
	while (i >= 0)
	{
		x = (*start % 8);
		y = (*start / 8);
		res |= ((buff[y] >> abs(7 - x)) & 1) << i;
		(*start)++;
		i--;
	}
	return (res);
}


void write_to_file(char *fname, char *buff, uint32_t buff_len)
{
	int fd;

	fd = open(fname, O_WRONLY | O_CREAT, S_IRWXU);
	write(fd, buff, buff_len);
	free(buff);
}
