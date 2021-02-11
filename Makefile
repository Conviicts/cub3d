NAME		=	cub3D
CC			=	gcc
FLAGS		=	-Wall -Werror -Wextra -I $(HEADER) -I $(MLX_PATH) -I $(LIBFT)

HEADER		=	./includes/
PARSING		=	./srcs/parsing/
UTILS		=	./srcs/utils/
ENGINE		=	./srcs/engine/
MLX_PATH	=	./minilibx-linux/
LIBFT		=	./libft/
SRCS		=	srcs/main.c									\
				$(addprefix ${UTILS}, write_error.c)		\
				$(addprefix ${UTILS}, color.c)				\
				$(addprefix ${PARSING}, init.c)				\
				$(addprefix ${PARSING}, check_args.c)		\
				$(addprefix ${PARSING}, map.c)				\
				$(addprefix ${PARSING}, map_length.c)		\
				$(addprefix ${PARSING}, map_args.c)			\
				$(addprefix ${PARSING}, map_validity.c)		\
				$(addprefix ${PARSING}, get_next_line.c)	\
				$(addprefix ${ENGINE}, init_mlx.c)			\
				$(addprefix ${ENGINE}, textures.c)			\
				$(addprefix ${ENGINE}, game.c)				\
				$(addprefix ${ENGINE}, raycasting.c)		\
				$(addprefix ${ENGINE}, player.c)			\
				$(addprefix ${ENGINE}, image.c)				\
				$(addprefix ${ENGINE}, draw.c)				\
				$(addprefix ${ENGINE}, input.c)				\
				$(addprefix ${ENGINE}, sprite.c)			\
				$(addprefix ${ENGINE}, sprite_utils.c)		\
				$(addprefix ${ENGINE}, bmp.c)				\

.c.o:
				$(CC) $(FLAGS) -c $< -o ${<:.c=.o}

OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(HEADER)
			make -C $(LIBFT)
			make -C $(MLX_PATH)
			$(CC) -o $(NAME) $(FLAGS) $(MLX) $(OBJS) -L$(LIBFT) -L$(MLX_PATH) -lft -lmlx -lm -lbsd -lX11 -lXext

clean		:
			rm -rf $(OBJS)
			make clean -C $(LIBFT)
			make clean -C $(MLX_PATH)

fclean		:	clean
			rm -f $(NAME)
			make fclean -C $(LIBFT)

re			:	fclean all
