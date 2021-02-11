/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 17:37:21 by jode-vri          #+#    #+#             */
/*   Updated: 2021/01/27 15:01:11 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int		key_press(int code, t_game *g)
{
	if (code == KEY_QUIT)
		close_game(g);
	if (code == KEY_LEFT)
		g->player.left = 1;
	if (code == KEY_RIGHT)
		g->player.right = 1;
	if (code == KEY_LEFT1)
		g->player.turn_left = 1;
	if (code == KEY_RIGHT1)
		g->player.turn_right = 1;
	if (code == KEY_FORWARD)
		g->player.forward = 1;
	if (code == KEY_BACKWARD)
		g->player.backward = 1;
	return (0);
}

int		key_release(int code, t_game *g)
{
	if (code == KEY_LEFT)
		g->player.left = 0;
	if (code == KEY_RIGHT)
		g->player.right = 0;
	if (code == KEY_LEFT1)
		g->player.turn_left = 0;
	if (code == KEY_RIGHT1)
		g->player.turn_right = 0;
	if (code == KEY_FORWARD)
		g->player.forward = 0;
	if (code == KEY_BACKWARD)
		g->player.backward = 0;
	return (0);
}

void	turn_left(t_game *g)
{
	double	old_dir;
	double	old_plane;

	old_dir = g->player.dir.x;
	g->player.dir.x = g->player.dir.x * cos(g->player.rot_speed)
		- g->player.dir.y * sin(g->player.rot_speed);
	g->player.dir.y = old_dir * sin(g->player.rot_speed)
		+ g->player.dir.y * cos(g->player.rot_speed);
	old_plane = g->player.plane.x;
	g->player.plane.x = g->player.plane.x * cos(g->player.rot_speed)
		- g->player.plane.y * sin(g->player.rot_speed);
	g->player.plane.y = old_plane * sin(g->player.rot_speed)
		+ g->player.plane.y * cos(g->player.rot_speed);
}

void	turn_right(t_game *g)
{
	double	old_dir;
	double	old_plane;

	old_dir = g->player.dir.x;
	g->player.dir.x = g->player.dir.x * cos(-g->player.rot_speed)
		- g->player.dir.y * sin(-g->player.rot_speed);
	g->player.dir.y = old_dir * sin(-g->player.rot_speed)
		+ g->player.dir.y * cos(-g->player.rot_speed);
	old_plane = g->player.plane.x;
	g->player.plane.x = g->player.plane.x * cos(-g->player.rot_speed)
		- g->player.plane.y * sin(-g->player.rot_speed);
	g->player.plane.y = old_plane * sin(-g->player.rot_speed)
		+ g->player.plane.y * cos(-g->player.rot_speed);
}

void	turn(t_game *g)
{
	if (g->player.turn_right)
		turn_left(g);
	else if (g->player.turn_left)
		turn_right(g);
}
