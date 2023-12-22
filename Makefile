CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = pipex_bonus.c pipex_find_path.c pipex_free.c pipex_handle_init.c pipex_fork_childs.c ft_split.c pipex_helper.c ft_bzero.c
TARGET = pipex

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

.PHONY: clean

clean:
	rm -f $(TARGET)
