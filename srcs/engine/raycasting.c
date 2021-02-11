/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 18:51:45 by jode-vri          #+#    #+#             */
/*   Updated: 2021/01/27 15:01:11 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	init_raycasting(t_game *g, int i)
{
	g->draw.camera_x = 2 * i / (double)g->window.width - 1;
	g->draw.ray_dir.x = g->player.dir.x + g->player.plane.x
		* g->draw.camera_x;
	g->draw.ray_dir.y = g->player.dir.y + g->player.plane.y
		* g->draw.camera_x;
	g->draw.map.x = (int)g->player.pos.x;
	g->draw.map.y = (int)g->player.pos.y;
	g->draw.delta_dist.x = fabs(1 / g->draw.ray_dir.x);
	g->draw.delta_dist.y = fabs(1 / g->draw.ray_dir.y);
}

void	init_raycasting_two(t_game *g)
{
	if (g->draw.ray_dir.x < 0)
	{
		g->draw.step.x = -1;
		g->draw.side_dist.x = (g->player.pos.x - g->draw.map.x)
			* g->draw.delta_dist.x;
	}
	else
	{
		g->draw.step.x = 1;
		g->draw.side_dist.x = (g->draw.map.x + 1.0 - g->player.pos.x)
			* g->draw.delta_dist.x;
	}
	if (g->draw.ray_dir.y < 0)
	{
		g->draw.step.y = -1;
		g->draw.side_dist.y = (g->player.pos.y - g->draw.map.y)
			* g->draw.delta_dist.y;
	}
	else
	{
		g->draw.step.y = 1;
		g->draw.side_dist.y = (g->draw.map.y + 1.0 - g->player.pos.y)
			* g->draw.delta_dist.y;
	}
}

void	dda(t_game *g)
{
	while (!g->draw.hit)
	{
		if (g->draw.side_dist.x < g->draw.side_dist.y)
		{
			g->draw.side_dist.x += g->draw.delta_dist.x;
			g->draw.map.x += g->draw.step.x;
			g->draw.side = 0;
			if (g->draw.step.x == 1)
				g->draw.cur_tex = &g->texture.east;
			else
				g->draw.cur_tex = &g->texture.west;
		}
		else
		{
			g->draw.side_dist.y += g->draw.delta_dist.y;
			g->draw.map.y += g->draw.step.y;
			g->draw.side = 1;
			if (g->draw.step.y == 1)
				g->draw.cur_tex = &g->texture.south;
			else
				g->draw.cur_tex = &g->texture.north;
		}
		if (g->map.map[(int)g->draw.map.y][(int)g->draw.map.x] == '1')
			g->draw.hit = 1;
	}
}

void	dda_next(t_game *g, int i)
{
	if (g->draw.side == 0)
		g->draw.perpwalldist = (g->draw.map.x - g->player.pos.x
				+ (1 - g->draw.step.x) / 2) / g->draw.ray_dir.x;
	else
		g->draw.perpwalldist = (g->draw.map.y - g->player.pos.y
				+ (1 - g->draw.step.y) / 2) / g->draw.ray_dir.y;
	g->draw.line_height = (int)(g->window.height / g->draw.perpwalldist);
	g->draw.draw_start = -g->draw.line_height / 2 + g->window.height / 2;
	if (g->draw.draw_start < 0)
		g->draw.draw_start = 0;
	g->draw.draw_end = g->draw.line_height / 2 + g->window.height / 2;
	if (g->draw.draw_end >= g->window.height)
		g->draw.draw_end = g->window.height - 1;
	g->draw.buffer[i] = g->draw.perpwalldist;
	get_texture_pixel(g, i, g->draw.cur_tex);
}

int		raycasting(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->window.width)
	{
		init_raycasting(game, i);
		init_raycasting_two(game);
		game->draw.hit = 0;
		dda(game);
		dda_next(game, i);
		i++;
	}
	draw_sprites(game);
	if (game->save)
		draw_bmp(game);
	else
	{
		mlx_put_image_to_window(game->window.mlx, game->window.win,
		game->img.ptr, 0, 0);
		mlx_destroy_image(game->window.mlx, game->img.ptr);
		game->img = create_image(game);
	}
	return (1);
}
