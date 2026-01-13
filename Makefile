
SRC = utility.c color.c formula.c fractol.c
OBJS =$(SRC:.c=.o)
NAME = fractol
CC = cc
FLAGS = -Wall -Wextra -Werror -g3
MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a

all: $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(FLAGS) $(OBJS) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
