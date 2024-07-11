NAME = cubed

LIBFT_PATH = libft/
LIBFT = $(addprefix $(LIBFT_PATH), libft.a)

MLX_PATH = mlx/
MLX = $(addprefix $(MLX_PATH), libmlx.a)
MLX_INCLUDE =  -lXext -lX11 -lm
MLX_GIT = git clone https://github.com/42Paris/minilibx-linux.git mlx
CLONE_MLX = @if [ -d "mlx/" ]; then \
    			:; \
			else \
    			$(MLX_GIT) > /dev/null 2>&1; \
				echo "cloned MLX"; \
			fi

PARSING_SRC = parsing.c
RAYCASTER_SRC = raycaster.c

RAYCATSER = $(addprefix raycaster/, $(RAYCASTER_SRC))
PARSING = $(addprefix parsing/, $(PARSING_SRC))
MAIN = main.c

SRC = $(addprefix src/, $(RAYCASTER) $(MAIN) $(PARSING))

OBJS = $(SRC:.c=.o)

COMPILE = cc -Wall -Wextra -Werror -g


all: $(NAME)

%.o: %.c
		$(CLONE_MLX)
		$(COMPILE) -c $< -o $@	
$(NAME): $(OBJS)
		@echo "all compiled"
		@make -C $(LIBFT_PATH)
		@make --silent -C $(MLX_PATH) > /dev/null 2>&1
		$(COMPILE) $(OBJS) $(LIBFT) $(MLX) $(MLX_INCLUDE) -o $(NAME)
		echo "     █████████  █████  █████ ███████████   ████████  ██████████ ";
		echo "    ███░░░░░███░░███  ░░███ ░░███░░░░░███ ███░░░░███░░███░░░░███ ";
		echo "   ███     ░░░  ░███   ░███  ░███    ░███░░░    ░███ ░███   ░░███ ";
		echo "  ░███          ░███   ░███  ░██████████    ██████░  ░███    ░███ ";
		echo "  ░███          ░███   ░███  ░███░░░░░███  ░░░░░░███ ░███    ░███ ";
		echo "  ░░███     ███ ░███   ░███  ░███    ░███ ███   ░███ ░███    ███ ";
		echo "   ░░█████████  ░░████████   ███████████ ░░████████  ██████████ ";
		echo "    ░░░░░░░░░    ░░░░░░░░   ░░░░░░░░░░░   ░░░░░░░░  ░░░░░░░░░░ ";
clean:
		@echo "clean"
		@make -C $(LIBFT_PATH) clean;
		@if [ -d "mlx/" ]; then \
				make --silent -C $(MLX_PATH) clean > /dev/null 2>&1; \
		fi
		rm -rf $(OBJS)

fclean: clean
		@echo "fclean"
		make -C $(LIBFT_PATH) fclean
		rm -rf $(NAME)
		rm -rf mlx/

re: fclean all


.DEFAULT:
	@echo "Usage: ./cubed path/to/map"

.SILENT:

.PHONY: all clean fclean
