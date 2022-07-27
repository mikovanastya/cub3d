NAME = cub3D

CC = cc
RM = rm -f

FLAGS = -Wall -Wextra -Werror

HEADERS =	./src/cub3d.h \
			./src/const.h \
			./src/libft/ft_zalloc/ft_zalloc.h \
			./src/libft/ft_get_next_line/get_next_line.h \
			./src/libft/libft.h \
			./src/env/env.h \
			./src/error/error.h \
			./src/hooks/hooks.h \
			./src/parser/parser.h \
			./src/render/render.h \
			./src/vector/vector.h

LIBFT		=	./src/libft/libft.a
LIBFT_DIR	=	./src/libft

MLXFLAGS	=	-L ./src/minilibx/ -lmlx -framework OpenGL -framework AppKit -lz
MLXDIR		=	./src/minilibx/

MAIN_SRCS	=	main \
				env/env \
				error/error \
				hooks/hooks \
				parser/check_properties \
				parser/get_properties \
				parser/get_map \
				parser/validate_input \
				render/image \
				render/raycasting \
				render/render_minimap \
				render/render_walls \
				render/render \
				vector/vector_operations1 \
				vector/vector_operations2

MAIN_SRC = $(addprefix ./src/, $(addsuffix .c, $(MAIN_SRCS)))

MAIN_OBJ = $(addprefix ./src/, $(addsuffix .o, $(MAIN_SRCS)))

all: $(NAME)

$(NAME): $(LIBFT) $(MAIN_OBJ) $(HEADERS)
	make bonus -s -C $(LIBFT_DIR)
	make -s -C $(MLXDIR)
	$(CC) $(FLAGS) $(MAIN_OBJ) $(LIBFT) $(MLXFLAGS) -lm -o $(NAME)

%.o: %.c Makefile $(HEADERS)
	$(CC) $(FLAGS) -Imlx -c $< -o $@ -I ./src/libft/

$(LIBFT): ./src/libft/ft_zalloc/*.c ./src/libft/ft_zalloc/*.h ./src/libft/*.c ./src/libft/*.h ./src/libft/Makefile
	make -C ./src/libft/

clean:
	$(RM) $(MAIN_OBJ)

fclean: clean
	$(RM) $(NAME)
	make clean -s -C $(MLXDIR)
	make fclean -s -C $(LIBFT_DIR)

run_room: all
	./cub3D src/maps/room.cub

run_anime: all
	./cub3D src/maps/anime.cub

run_test: all
	./cub3D src/maps/test.cub

re: fclean all

.PHONY: all clean fclean re run_anime run_test run_room