/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 13:45:43 by jode-vri          #+#    #+#             */
/*   Updated: 2021/01/27 15:47:20 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"

# define KEY_QUIT 65307
# define KEY_FORWARD 119
# define KEY_BACKWARD 115
# define KEY_LEFT 97
# define KEY_LEFT1 65361
# define KEY_RIGHT 100
# define KEY_RIGHT1 65363
# define TMA "Too many args\n[USAGE]: ./cub3d map_file.cub <--save>"
# define WA "Wrong args\n[USAGE]: ./cub3d map_file.cub <--save>"
# define NEA "Not enough args\n[USAGE]: ./cub3d map_file.cub <--save>"
# define R_ERROR "Wrong red color value, it must be between 0 and 255"
# define G_ERROR "Wrong green color value, it must be between 0 and 255"
# define B_ERROR "Wrong blue color value, it must be between 0 and 255"
# define BCC_ERROR "Wrong character in color, it must be '0-255, 0-255, 0-255'"

typedef struct	s_pos
{
	double		x;
	double		y;
}				t_pos;

typedef struct	s_ipos
{
	int			x;
	int			y;
}				t_ipos;

typedef struct	s_size
{
	double		w;
	double		h;
}				t_size;

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
	int			is_r;
	int			is_g;
	int			is_b;
}				t_color;

typedef struct	s_img
{
	void		*ptr;
	int			*data;
	int			bpp;
	int			size;
	int			endian;
}				t_img;

typedef struct	s_xpm
{
	char		*path;
	t_img		img;
	int			width;
	int			height;
}				t_xpm;

typedef struct	s_map
{
	char		**map;
	char		*map_path;
	int			height;
}				t_map;

typedef struct	s_texture
{
	t_xpm		north;
	t_xpm		south;
	t_xpm		west;
	t_xpm		east;
	t_xpm		sprite;
	t_color		floor;
	t_color		ceiling;
}				t_texture;

typedef struct	s_player
{
	double		speed;
	double		rot_speed;
	int			forward;
	int			backward;
	int			turn_right;
	int			turn_left;
	int			right;
	int			left;
	t_pos		pos;
	char		orient;
	t_pos		dir;
	t_pos		plane;
}				t_player;

typedef struct	s_window
{
	void		*mlx;
	void		*win;
	int			width;
	int			height;
}				t_window;

typedef struct	s_draw
{
	double		camera_x;
	t_pos		ray_dir;
	t_pos		map;
	t_pos		delta_dist;
	t_pos		side_dist;
	t_ipos		step;
	double		perpwalldist;
	double		*buffer;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			side;
	int			tmp;
	int			hit;
	t_xpm		*cur_tex;
}				t_draw;

typedef struct	s_bmp
{
	char		*header;
	int			color;
	int			fd;
}				t_bmp;

typedef struct	s_sprite
{
	t_pos		t;
	t_ipos		texture;
	t_pos		pos;
	t_pos		draw_start;
	t_pos		draw_end;
	t_size		size;
	double		poss;
	int			color;
	int			dist;
	int			screen;
}				t_sprite;

typedef struct	s_game
{
	t_window	window;
	int			save;
	int			fd;
	t_ipos		screen_size;
	t_map		map;
	t_texture	texture;
	t_player	player;
	t_draw		draw;
	t_img		img;
	t_sprite	*sprites;
	char		*error;
	int			sprite_count;
	char		*gnl_tmp;
	char		*gnl_line;
}				t_game;

int				get_next_line(int fd, char **line, t_game *game);
void			init_game(t_game *game);
int				write_error(t_game *game, char *error);
int				check_args(t_game *game, int ac, char **av);
int				init_map(t_game *game);
int				parse_map(t_game *game);
int				get_map_length(t_game *game, char *name);
int				set_window_resolution(t_game *game, char *line);
int				set_textures(t_game *g, char *line, char **texture, int s);
int				set_colors(t_game *g, char *line, t_color *color);
int				check_map_validity(t_game *game, t_map *map);
int				init_mlx(t_game *game);
int				close_game(t_game *game);
int				game_loop(t_game *game);
int				raycasting(t_game *game);
void			init_textures(t_game *game);
t_img			create_image(t_game *game);
int				init_player(t_game *game, t_player *player);
void			draw_texture(t_game *g, int column, t_xpm *texture, int x);
void			set_orientation(t_game *game, char orient);
void			get_texture_pixel(t_game *g, int col, t_xpm *texture);
void			move_player(t_game *g);
int				key_press(int code, t_game *g);
int				key_release(int code, t_game *g);
void			draw_pixels(t_game *g, int x, int y, int color);
void			draw_health_bar(t_game *game);
int				rgb_to_decimal(t_color color);
void			init_sprites(t_game *game);
void			draw_sprites(t_game *g);
void			walk(t_game *g);
void			turn(t_game *g);
void			straf(t_game *g);
void			get_draw_start_end(t_game *g, int id);
void			get_sprite_position(t_game *g, int id);
void			draw_sprite(t_game *g, int id, int i);
void			draw_bmp(t_game *game);
int				check_vars(t_game *g);
int				check_comma(t_game *g, int nb);
#endif
