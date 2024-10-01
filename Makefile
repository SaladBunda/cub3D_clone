CC = cc
FLAGS = -Wall -Wextra -Werror -O3
ENTRY = ./mandatory/cub3d.c
SRCS =	./mandatory/srcs/init.c \
./mandatory/srcs/map.c \
./mandatory/srcs/hooks.c \
./mandatory/srcs/raycast.c \
./mandatory/srcs/intersec.c \
./mandatory/srcs/utils.c \
./mandatory/srcs/moves.c
OBJS = $(SRCS:%.c=%.o)
OBJS_BON = $(SRCS_BON:%.c=%.o)
INCLUDE = ./mandatory/cub3d.h
MLX_MACOS = -framework Cocoa -framework OpenGL -framework IOKit
MLX_INCLUDE = ./MLX42/include/MLX42.h
MLX42_DIR = ./MLX42
GLFW = -lglfw -L/Users/ael-maaz/.brew/opt/glfw/lib/
MLX_AR = ./MLX42/build/libmlx42.a
MLXLIB = ./MLX42/lib/MLX42
FSANITIZE = -g -fsanitize=address
LIBR = libr.a
NAME = cub3D

all: $(MLX_AR) $(LIBR) $(NAME)

bonus : $(MLX_AR) $(NAME_BON)

$(LIBR):
	make -C libr

$(MLX42_DIR):
	@echo "Cloning MLX42..."
	@git clone https://github.com/codam-coding-college/MLX42.git > /dev/null 2>&1
	@echo "MLX42 has been successfully cloned."

$(MLX_AR): $(MLX42_DIR)
	@echo "Building MLX42..."
	@git submodule update --init --recursive
	@cd MLX42 && cmake -B build && cmake --build build -j4 > /dev/null 2>&1
	@echo "MLX42 has been successfully built." > /dev/null 2>&1

$(NAME): $(INCLUDE) $(OBJS)
	make -C mandatory
clean:
	make clean -C mandatory
	make clean -C libr
fclean: clean
	rm -rf $(NAME) $(NAME_BON)
	make fclean -C libr
re: fclean all
