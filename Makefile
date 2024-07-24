NAME = cub3D

LIBFT_PATH = libft/
LIBFT = $(addprefix $(LIBFT_PATH), libft.a)

MLX_PATH = mlx/
MLX = $(addprefix $(MLX_PATH), libmlx.a)
MLX_INCLUDE =  -lXext -lX11 -lm
MLX_GIT = git clone https://github.com/42Paris/minilibx-linux.git mlx
CLONE_MLX = @if [ -d "mlx/" ]; then \
    			:; \
			else \
				echo "\e[0;33mcloning\e[0m -> \e[0;32mMLX\e[0m"; \
    			$(MLX_GIT) > /dev/null 2>&1; \
			fi

PARSING_SRC = 	parsing.c parsing_2.c checks_color.c checks_surface.c \
				parsing_checks.c
RAYCASTER_SRC = raycaster.c
UTILS_SRC = 	close_and_err.c mlx_utils.c
INIT_SRC = 		init.c
GAME_SRC = 		texture.c game_loop.c movment.c collision_check.c interactable.c

GAME = $(addprefix game/, $(GAME_SRC))
INIT = $(addprefix init/, $(INIT_SRC))
RAYCASTER = $(addprefix raycaster/, $(RAYCASTER_SRC))
PARSING = $(addprefix parsing/, $(PARSING_SRC))
UTILS = $(addprefix utils/, $(UTILS_SRC))
MAIN = main.c

SRC = $(addprefix src/, $(GAME) $(MAIN) \
						$(PARSING) $(UTILS) $(INIT) $(RAYCASTER))

OBJS = $(SRC:.c=.o)

COMPILE = cc -Wall -Wextra -Werror -g

BLK = "\e[0;30m"
RED = "\e[0;31m"
GRN = "\e[0;32m"
YEL = "\e[0;33m"
BLU = "\e[0;34m"
MAG = "\e[0;35m"
CYN = "\e[0;36m"
WHT = "\e[0;37m"
CRESET = "\e[0m" 	

all: $(NAME)

%.o: %.c
		$(CLONE_MLX)
		$(COMPILE) -c $< -o $@

$(NAME): $(OBJS)
		@echo "\e[0;33mCompiling\e[0m -> \e[0;37mLIBFT\e[0m"
		@make -C $(LIBFT_PATH)
		@echo "\e[0;32mDone\e[0m"
		@echo "\e[0;33mCompiling \e[0m-> \e[0;37mMLX\e[0m"
		@make --silent -C $(MLX_PATH) 2> /dev/null
		@echo "\e[0;32mDone\e[0m"
		$(COMPILE) $(OBJS) $(LIBFT) $(MLX) $(MLX_INCLUDE) -o $(NAME)
		@CLR="\033[36m"; \
		NC="\033[0m"; \
		echo ""; \
		echo "    █████████  █████  █████ ███████████ $${CLR}  ████████  ██████████ $${NC}"; \
		echo "   ███░░░░░███░░███  ░░███ ░░███░░░░░███$${CLR} ███░░░░███░░███░░░░███ $${NC}"; \
		echo "  ███     ░░░  ░███   ░███  ░███    ░███$${CLR}░░░    ░███ ░███   ░░███ $${NC}"; \
		echo " ░███          ░███   ░███  ░██████████ $${CLR}   ██████░  ░███    ░███ $${NC}"; \
		echo " ░███          ░███   ░███  ░███░░░░░███$${CLR}  ░░░░░░███ ░███    ░███ $${NC}"; \
		echo " ░░███     ███ ░███   ░███  ░███    ░███$${CLR} ███   ░███ ░███    ███ $${NC}"; \
		echo "  ░░█████████  ░░████████   ███████████ $${CLR}░░████████  ██████████ $${NC}"; \
		echo "   ░░░░░░░░░    ░░░░░░░░   ░░░░░░░░░░░  $${CLR} ░░░░░░░░  ░░░░░░░░░░ $${NC}"; \
		echo ""
clean:
		@echo "\e[0;35mCleaning\e[0m -> \e[0;37mLIBFT\e[0m"
		@make --silent -C $(LIBFT_PATH) clean /dev/null 2>&1;
		@if [ -d "mlx/" ]; then \
				echo "\e[0;35mCleaning\e[0m -> \e[0;37mMLX\e[0m"; \
				make --silent -C $(MLX_PATH) clean; \
		fi
		@echo "\e[0;35mCleaning\e[0m -> \e[0;37mOBJS\e[0m"
		rm -rf $(OBJS)

fclean: clean
		make -C $(LIBFT_PATH) fclean
		rm -rf $(NAME)

re: fclean all

destroy: fclean
		rm -rf mlx/

.DEFAULT:
	@echo " \t =========\n\
		 | \e[0;95mCUB3D\e[0m |\n\
		 =========\n\n\
No rule called '\e[1;31m$@\e[0m'\n\
\e[1;32mUsage\e[0m: \e[1;37m make: \e[1;32mall \e[0m- \e[1;32mclean \e[0m- \e[1;32mfclean \e[0m\n"

.SILENT:

.PHONY: all clean fclean
