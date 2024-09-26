CC = cc
CFLAGS = -Wall -Werror -Wextra -g
SRC = pipex_bonus.c pipex_find_path.c pipex_free.c pipex_handle_init.c pipex_fork_childs.c ft_split.c pipex_helper.c ft_bzero.c pipex_helper2.c
TARGET = pipex

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
