/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 02:15:12 by jode-vri          #+#    #+#             */
/*   Updated: 2021/01/27 15:01:11 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	draw_pixels(t_game *g, int x, int y, int color)
{
	g->img.data[y * (g->img.size / 4) + x] = color;
}

void	draw_texture(t_game *g, int column, t_xpm *texture, int x)
{
	double	pos;
	double	step;
	int		i;

	i = -1;
	step = 1.0 * texture->height / g->draw.line_height;
	pos = (g->draw.draw_start - g->window.height / 2
			+ g->draw.line_height / 2) * step;
	while (++i < g->window.height)
	{
		if (i >= g->draw.draw_start && i <= g->draw.draw_end)
		{
			draw_pixels(g, column, i, texture->img.data[(int)pos
			* (texture->img.size / 4) + x]);
			pos += step;
		}
		else if (i < g->window.height / 2)
			draw_pixels(g, column, i, rgb_to_decimal(g->texture.ceiling));
		else
			draw_pixels(g, column, i, rgb_to_decimal(g->texture.floor));
	}
}

void	get_texture_pixel(t_game *g, int col, t_xpm *texture)
{
	double	wall;
	int		pos;

	if (g->draw.side == 0)
		wall = g->player.pos.y + g->draw.perpwalldist * g->draw.ray_dir.y;
	else
		wall = g->player.pos.x + g->draw.perpwalldist * g->draw.ray_dir.x;
	wall -= floor(wall);
	pos = (int)(wall * (double)texture->width);
	if (g->draw.side == 0 && g->draw.ray_dir.x > 0)
		pos = texture->width - pos - 1.0;
	if (g->draw.side == 1 && g->draw.ray_dir.y < 0)
		pos = texture->width - pos - 1.0;
	draw_texture(g, col, texture, pos);
}
