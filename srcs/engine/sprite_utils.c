/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 02:15:00 by jode-vri          #+#    #+#             */
/*   Updated: 2021/01/27 15:01:11 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	get_draw_start_end(t_game *g, int id)
{
	g->sprites[id].draw_start.y = -g->sprites[id].size.h
		/ 2 + g->window.height / 2;
	if (g->sprites[id].draw_start.y < 0)
		g->sprites[id].draw_start.y = 0;
	g->sprites[id].draw_end.y = g->sprites[id].size.h
		/ 2 + g->window.height / 2;
	if (g->sprites[id].draw_end.y >= g->window.height)
		g->sprites[id].draw_end.y = g->window.height - 1;
	g->sprites[id].size.w = abs((int)(g->window.height
				/ (g->sprites[id].t.y)));
	g->sprites[id].draw_start.x = -g->sprites[id].size.w
		/ 2 + g->sprites[id].screen;
	if (g->sprites[id].draw_start.x < 0)
		g->sprites[id].draw_start.x = 0;
	g->sprites[id].draw_end.x = g->sprites[id].size.w
		/ 2 + g->sprites[id].screen;
	if (g->sprites[id].draw_end.x >= g->window.width)
		g->sprites[id].draw_end.x = g->window.width - 1;
}

void	get_sprite_position(t_game *g, int id)
{
	double	x;
	double	y;

	x = g->sprites[id].pos.x - g->player.pos.x + .5;
	y = g->sprites[id].pos.y - g->player.pos.y + .5;
	g->sprites[id].poss = 1.0 / (g->player.plane.x
			* g->player.dir.y - g->player.dir.x * g->player.plane.y);
	g->sprites[id].t.x = g->sprites[id].poss
		* (g->player.dir.y * x - g->player.dir.x * y);
	g->sprites[id].t.y = g->sprites[id].poss
		* (-g->player.plane.y * x + g->player.plane.x * y);
	g->sprites[id].screen = (int)((g->window.width / 2) * (1 +
		g->sprites[id].t.x / g->sprites[id].t.y));
	g->sprites[id].size.h = abs((int)(g->window.height
				/ (g->sprites[id].t.y)));
	get_draw_start_end(g, id);
}

void	draw_sprite(t_game *g, int id, int i)
{
	int	j;

	j = g->sprites[id].draw_start.y - 1;
	while (++j < g->sprites[id].draw_end.y)
	{
		g->sprites[id].texture.y = (((j * 256 - g->window.height * 128 +
		g->sprites[id].size.h * 128) * g->texture.sprite.height) /
		g->sprites[id].size.h) / 256;
		g->sprites[id].color = g->texture.sprite.img.data[
			g->sprites[id].texture.y * 64 + g->sprites[id].texture.x];
		if (g->sprites[id].color != 0)
			draw_pixels(g, i, j, g->sprites[id].color);
	}
}
