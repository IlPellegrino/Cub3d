NAME = Cub3d

LIBFT_PATH = libft/
LIBFT = $(addprefix $(LIBFT_PATH), libft.a)

MLX_PATH = mlx/
MLX = $(addprefix $(MLX_PATH), libmlx.a)

SRC = src/parsing.c src/raycaster.c main.c

OBJS = $(SRC:.c=.o)

COMPILE = cc -Wall -Wextra -Werror -g -lmlx -lXext -lX11 -lm

all: $(NAME)

%.o: %.c
		$(COMPILE) -c $< -o $@	
$(NAME): $(OBJS)

		make -C $(LIBFT_PATH)
		$(COMPILE) $(OBJS) -o $(NAME) $(LIBFT)

clean:
		make -C $(LIBFT_PATH) clean
		rm -rf $(OBJS)

fclean: clean
		make -C $(LIBFT_PATH) fclean
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean
