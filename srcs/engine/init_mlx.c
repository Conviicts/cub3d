/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 22:26:56 by jode-vri          #+#    #+#             */
/*   Updated: 2021/01/27 15:07:15 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	move_player(t_game *g)
{
	turn(g);
	straf(g);
	walk(g);
}

void	init_mlx2(t_game *game)
{
	if (game->save)
		raycasting(game);
	else
	{
		mlx_hook(game->window.win, 33, 1L << 0, close_game, game);
		mlx_hook(game->window.win, 2, 1L << 0, key_press, game);
		mlx_hook(game->window.win, 3, 1L << 1, key_release, game);
		mlx_loop_hook(game->window.mlx, game_loop, game);
		mlx_loop(game->window.mlx);
	}
}

int		init_mlx(t_game *game)
{
	game->window.mlx = mlx_init();
	mlx_get_screen_size(game->window.mlx, &game->screen_size.x,
		&game->screen_size.y);
	if (game->window.width <= 0 || game->window.height <= 0)
		return (write_error(game, "Wrong resolution"));
	if (game->window.width > game->screen_size.x)
		game->window.width = game->screen_size.x;
	if (game->window.height > game->screen_size.y)
		game->window.height = game->screen_size.y;
	init_textures(game);
	if (!game->save)
		game->window.win = mlx_new_window(game->window.mlx, game->window.width,
			game->window.height, "Cub3D");
	game->img = create_image(game);
	game->draw.buffer = (double *)malloc(sizeof(double) * game->window.width);
	if (!game->draw.buffer)
		write_error(game, "Unable to malloc for sprite buffer");
	init_sprites(game);
	init_mlx2(game);
	return (1);
}
