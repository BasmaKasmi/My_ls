CC = gcc
CFLAGS = -Wall -Wextra -Werror
INC = -Iinclude
SRCS = src/main.c src/list.c src/parse.c
OBJS = $(SRCS:.c=.o)
EXEC = my_ls

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(INC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f src/*.o

fclean: clean
	rm -f $(EXEC)

re: fclean all

.PHONY: all clean fclean re
