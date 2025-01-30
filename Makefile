NAME = so_long

SRC = parsing.c get_next_line.c get_next_line_utils.c
OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_LIB)
	make -C libft
	$(CC) $(CFLAGS) $(OBJ) libft/libft.a -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -o $(NAME) -lX11 -lXext
	
clean:
	@make -C libft clean
	rm -f $(OBJ)

fclean: clean
	@make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re