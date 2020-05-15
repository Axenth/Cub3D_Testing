NAME = cub3D

SRC = main.c key.c draw.c camera.c ray.c map.c \
	  player_movement.c error_handeling.c parser/resolution.c \
	  parser/floor_ceiling_color.c parser/player_position.c \
	  screenshot/bitmap_header.c parser/enclosed_map.c \
	  safety.c map2.c parser/enclosed_map_2.c draw_sprites.c \
	  draw_sprites2.c calc_draw.c set_textures.c rotation.c \
	  map3.c parser/verification.c screenshot/bitmap_safety.c \
	  init.c

SRC_MAP = srcs/

SRCS = $(addprefix $(SRC_MAP), $(SRC))

LIBS = libft/libft.a libmlx.dylib

HDRS = -I mlx -I libft/hdrs -I hdrs/

OPT_FLAGS = -O2

$(NAME): all

all: libft lib
	@echo "\033[0;31m"Compiling Cub3d
	@echo "\033[0;34m"
	gcc -o $(NAME) $(SRCS) $(LIBS) $(HDRS) -lm -Lmlx -framework OpenGL -framework AppKit -lm -g -Wall -Werror -Wextra 
	@echo "\033[0;32m""Done - Run ./$(NAME)"

sanitize: libft lib
	@echo "\033[0;31m"Compiling Cub3d
	@echo "\033[0;34m"
	gcc -o $(NAME) $(SRCS) $(LIBS) $(HDRS) -lm -Lmlx -framework OpenGL -framework AppKit -lm -g -Wall -Werror -Wextra -fsanitize=address
	@echo "\033[0;32m""Done - Run ./$(NAME)"


libft:
	@echo "\033[0;31m"Compiling Libft
	@echo "\033[0;34m"
	@$(MAKE) -C  libft/ all
	
lib:
	@echo "\033[0;31m"Compiling minilibx
	@echo "\033[0;34m"
	@$(MAKE) -C mlx/ all
	@mv mlx/libmlx.dylib ./libmlx.dylib

clean: 
	@echo "Cleaning\033[0;31m"
	@$(MAKE) -C libft/ clean
	@$(MAKE) -C mlx/ clean
	@echo "\033[0;32m"Done

fclean: 
	@echo "Force Cleaning\033[0;31m"
	@$(MAKE) -C libft/ fclean
	@$(MAKE) -C mlx/ clean
	@rm -f libmlx.dylib
	@rm -f $(NAME)
	@echo "\033[0;32m"Done

re: fclean all

.PHONY: all libft lib clean fclean re
