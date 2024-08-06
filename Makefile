NAME = cub3D
NAME_BONUS = cub3D_bonus

LIBFT_PATH = libft/
LIBFT = $(addprefix $(LIBFT_PATH), libft.a)

MLX_PATH = mlx/
MLX = $(addprefix $(MLX_PATH), libmlx.a)
MLX_INCLUDE = -lXext -lX11 -lm -lbsd
MLX_GIT = git clone https://github.com/42Paris/minilibx-linux.git mlx
CLONE_MLX = @if [ -d "mlx/" ]; then \
				:; \
			else \
				echo "\e[0;33mcloning\e[0m -> \e[0;32mMLX\e[0m"; \
				$(MLX_GIT) > /dev/null 2>&1; \
			fi

# Sources
PARSING_SRC		= 	checks_color.c checks_surface.c parsing_utils.c
UTILS_SRC		=	utils.c draw_line.c
GAME_SRC		= 	input/input_manager.c collision_check.c \
				 	interactable.c input/input_keys.c movment/controls.c gui/gui.c \
					gui/minimap_gui.c input/change_settings.c gui/weapon.c

MAND = game/game_loop.c parsing/parsing.c parsing/parsing_2.c parsing/parsing_checks.c \
		raycaster/raycaster.c raycaster/walls.c raycaster/vertical_raycast.c \
		raycaster/horizontal_raycast.c raycaster/raycast_utils.c raycaster/direction_utils.c \
		utils/close_and_err.c game/texture.c init/init.c
		
BONUS = bonus_src/game_loop_bonus.c bonus_src/parsing_bonus.c bonus_src/parsing_2_bonus.c \
		bonus_src/parsing_checks_bonus.c bonus_src/raycaster_bonus.c bonus_src/walls_bonus.c \
		bonus_src/vertical_raycast_bonus.c bonus_src/horizontal_raycast_bonus.c \
		bonus_src/raycast_utils_bonus.c bonus_src/direction_utils_bonus.c \
		bonus_src/close_and_err_bonus.c bonus_src/texture_bonus.c bonus_src/init_bonus.c

GAME = $(addprefix game/, $(GAME_SRC))
PARSING = $(addprefix parsing/, $(PARSING_SRC))
UTILS = $(addprefix utils/, $(UTILS_SRC))
MAIN = main.c

SRC = $(addprefix src/, $(GAME) $(MAIN) \
						$(PARSING) $(UTILS) \
						$(MAND))

BONUS_SRC = $(addprefix src/, $(GAME) $(MAIN) \
						$(PARSING) $(UTILS) \
						$(BONUS))

OBJS = $(SRC:.c=.o)
BONUS_OBJS = $(BONUS_SRC:.c=.o)

COMPILE = cc -Wall -Wextra -Werror -g

ASCII_ART = @CLR="\033[36m"; \
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
	@make -C $(MLX_PATH) 2> /dev/null
	$(COMPILE) $(OBJS) -I include/cubed.h $(LIBFT) $(MLX) $(MLX_INCLUDE) -o $(NAME)
	$(ASCII_ART)

bonus: $(NAME_BONUS)
%.o: %.c
	$(CLONE_MLX)
	$(COMPILE) -c $< -o $@
$(NAME_BONUS): $(BONUS_OBJS)
	@echo "\e[0;33mCompiling bonus\e[0m -> \e[0;37mLIBFT\e[0m"
	@make -C $(LIBFT_PATH)
	@echo "\e[0;32mDone\e[0m"
	@echo "\e[0;33mCompiling bonus \e[0m-> \e[0;37mMLX\e[0m"
	@make -C $(MLX_PATH) 2> /dev/null
	$(COMPILE) $(BONUS_OBJS) -I include/cubed.h $(LIBFT) $(MLX) $(MLX_INCLUDE) -o $(NAME_BONUS)
	$(ASCII_ART)

clean:
	@echo "\e[0;35mCleaning\e[0m -> \e[0;37mLIBFT\e[0m"
	@make -C $(LIBFT_PATH) clean
	@if [ -d "mlx/" ]; then \
			echo "\e[0;35mCleaning\e[0m -> \e[0;37mMLX\e[0m"; \
			make -C $(MLX_PATH) clean; \
	fi
	@echo "\e[0;35mCleaning\e[0m -> \e[0;37mOBJS\e[0m"
	rm -rf $(OBJS) $(BONUS_OBJS)

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

.PHONY: all clean fclean re destroy bonus
