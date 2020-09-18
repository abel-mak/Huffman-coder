SRC	= $(wildcard src/*.c)
OBJ	= $(SRC:.c=.o)
FLAGS	= -Wall -Wextra -Werror
CC	= gcc
BIN	= huff

all: $(BIN)
$(BIN):$(OBJ)
	 $(CC) $(FLAGS) $(OBJ) -o $(BIN) -lm
%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@ 
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(BIN)
re: fclean all
memcheck:
	@echo "valgrind -v --show-leak-kinds=all --leak-check=full --track-origins=yes"
