/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 19:06:49 by jode-vri          #+#    #+#             */
/*   Updated: 2021/01/27 15:01:11 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	set_plane(t_game *game, char orient)
{
	if (orient == 'N')
	{
		game->player.plane.x = 0.66;
		game->player.plane.y = 0;
	}
	else if (orient == 'S')
	{
		game->player.plane.x = -0.66;
		game->player.plane.y = 0;
	}
	else if (orient == 'W')
	{
		game->player.plane.x = 0;
		game->player.plane.y = -0.66;
	}
	else if (orient == 'E')
	{
		game->player.plane.x = 0;
		game->player.plane.y = 0.66;
	}
}

void	set_orientation(t_game *game, char orient)
{
	if (orient == 'N')
	{
		game->player.dir.x = 0;
		game->player.dir.y = -1;
	}
	else if (orient == 'S')
	{
		game->player.dir.x = 0;
		game->player.dir.y = 1;
	}
	else if (orient == 'W')
	{
		game->player.dir.x = -1;
		game->player.dir.y = 0;
	}
	else if (orient == 'E')
	{
		game->player.dir.x = 1;
		game->player.dir.y = 0;
	}
	set_plane(game, orient);
}

void	straf(t_game *g)
{
	if (g->player.left)
	{
		if (g->map.map[(int)g->player.pos.y][(int)(g->player.pos.x
			- g->player.plane.x * g->player.speed)] == '0')
			g->player.pos.x -= g->player.plane.x * g->player.speed;
		if (g->map.map[(int)(g->player.pos.y - g->player.plane.y
			* g->player.speed)][(int)g->player.pos.x] == '0')
			g->player.pos.y -= g->player.plane.y * g->player.speed;
	}
	if (g->player.right)
	{
		if (g->map.map[(int)g->player.pos.y][(int)(g->player.pos.x
						+ g->player.plane.x * g->player.speed)] == '0')
			g->player.pos.x += g->player.plane.x * g->player.speed;
		if (g->map.map[(int)(g->player.pos.y + g->player.plane.y
					* g->player.speed)][(int)g->player.pos.x] == '0')
			g->player.pos.y += g->player.plane.y * g->player.speed;
	}
}

void	walk(t_game *g)
{
	if (g->player.forward)
	{
		if (ft_is_in_charset(g->map.map[(int)g->player.pos.y][(int)
				(g->player.pos.x + g->player.dir.x * g->player.speed)], "0"))
			g->player.pos.x += g->player.dir.x * g->player.speed;
		if (ft_is_in_charset(g->map.map[(int)(g->player.pos.y + g->player.dir.y
						* g->player.speed)][(int)g->player.pos.x], "0"))
			g->player.pos.y += g->player.dir.y * g->player.speed;
	}
	if (g->player.backward)
	{
		if (ft_is_in_charset(g->map.map[(int)g->player.pos.y][(int)
				(g->player.pos.x - g->player.dir.x * g->player.speed)], "0"))
			g->player.pos.x -= g->player.dir.x * g->player.speed;
		if (ft_is_in_charset(g->map.map[(int)(g->player.pos.y - g->player.dir.y
						* g->player.speed)][(int)g->player.pos.x], "0"))
			g->player.pos.y -= g->player.dir.y * g->player.speed;
	}
}
