#include "huffman.h"

int main(int argc, char **argv)
{
	int fd;
	struct stat st;
	int size;

	if (argc == 3)
	{
		fd = open(argv[2], O_RDONLY);
		fstat(fd, &st);
		size = st.st_size;
		if (fd == -1)
		{
			printf("file doesn't exist\n");
			return (1);
		}
		else if (strncmp(argv[1], "-e", 2) == 0)
			encode(fd, argv[2], size);
		else if (strncmp(argv[1], "-d", 2) == 0)
		{
			if (end_with(argv[2], ".huff") == 1)
				decode(fd, argv[2], size);
			else
				printf("file must be huffman file (ends with .huff)\n");
		}
		else
			printf("huff [-d] filename\nhuff [-e] filename\n");
	}
	else
		printf("huff [-d] filename\nhuff [-e] filename\n");
	return (0);
}
//Refference:
//http://www.cs.ecu.edu/~karl/3300/spr10/assignments/assn4.html
//https://www2.cs.duke.edu/csed/poop/huff/info/
//answers on uniqueness huffman tree: https://stackoverflow.com/questions/2994192/confused-about-huffman-trees/13819209#:~:text=Huffman%20codes%20can%20be%20different,so%20this%20doesn't%20matter.
//http://web.stanford.edu/class/archive/cs/cs106x/cs106x.1192/resources/minibrowser2/huffman-encoding-supplement.pdf
//https://en.wikipedia.org/wiki/Tree_traversal
