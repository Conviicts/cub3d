/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 21:06:53 by jode-vri          #+#    #+#             */
/*   Updated: 2021/01/27 15:01:11 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	get_sprite_dist(t_game *g)
{
	int	id;

	id = -1;
	while (++id < g->sprite_count)
	{
		g->sprites[id].dist = sqrt(pow(g->player.pos.x
		- g->sprites[id].pos.x, 2) + pow(g->player.pos.y
		- g->sprites[id].pos.y, 2));
	}
}

void	sort_sprites(t_game *g)
{
	int			i;
	t_sprite	tmp;

	get_sprite_dist(g);
	i = 0;
	while (i < g->sprite_count - 1)
	{
		if (g->sprites[i].dist < g->sprites[i + 1].dist)
		{
			tmp = g->sprites[i];
			g->sprites[i] = g->sprites[i + 1];
			g->sprites[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

void	draw_sprites(t_game *g)
{
	int	i;
	int	id;

	id = -1;
	sort_sprites(g);
	while (++id < g->sprite_count)
	{
		get_sprite_position(g, id);
		i = g->sprites[id].draw_start.x - 1;
		while (++i < g->sprites[id].draw_end.x)
		{
			g->sprites[id].texture.x = (int)(256 * (i - (-g->sprites[id].size.w
			/ 2 + g->sprites[id].screen)) * g->texture.sprite.width /
			g->sprites[id].size.w) / 256;
			if (g->sprites[id].t.y > 0 && i > 0
				&& i < g->window.width && g->sprites[id].t.y
				< g->draw.buffer[i])
				draw_sprite(g, id, i);
		}
	}
}

void	count_sprite_nb(t_game *game)
{
	int	x;
	int	y;

	game->sprite_count = 0;
	y = -1;
	while (++y < game->map.height)
	{
		x = -1;
		while (game->map.map[y][++x])
		{
			if (game->map.map[y][x] == '2')
				(game->sprite_count)++;
		}
	}
}

void	init_sprites(t_game *game)
{
	int	x;
	int	y;
	int	id;

	count_sprite_nb(game);
	game->sprites = (t_sprite *)malloc(sizeof(t_sprite)
			* game->sprite_count);
	if (game->sprites == NULL)
		write_error(game, "unable to malloc [sprites]");
	id = 0;
	y = -1;
	while (++y < game->map.height)
	{
		x = -1;
		while (game->map.map[y][++x])
		{
			if (game->map.map[y][x] == '2')
			{
				game->sprites[id].pos.x = x;
				game->sprites[id].pos.y = y;
				id++;
			}
		}
	}
}
