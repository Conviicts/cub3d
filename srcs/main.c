/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 15:16:02 by jode-vri          #+#    #+#             */
/*   Updated: 2021/01/27 16:29:30 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	setup_game(t_game *game)
{
	game->window.width = -1;
	game->window.height = -1;
	game->texture.floor.r = -1;
	game->texture.floor.g = -1;
	game->texture.floor.b = -1;
	game->texture.ceiling.r = -1;
	game->texture.ceiling.g = -1;
	game->texture.ceiling.b = -1;
	game->fd = -1;
	game->player.pos.x = -1;
	game->player.pos.y = -1;
	game->player.dir.x = -1;
	game->player.plane.y = 0.66;
	game->player.rot_speed = 0.05;
	game->player.speed = 0.05;
	game->player.forward = 0;
	game->player.backward = 0;
	game->player.left = 0;
	game->player.right = 0;
	game->player.turn_left = 0;
	game->player.turn_right = 0;
}

int		main(int ac, char **av)
{
	t_game	game;

	ft_bzero(&game, sizeof(game));
	ft_bzero(&game.map, sizeof(&game.map));
	ft_bzero(&game.player, sizeof(&game.player));
	setup_game(&game);
	check_args(&game, ac, av);
	if (!init_map(&game))
		return (write_error(&game, ""));
	if (!parse_map(&game))
		return (write_error(&game, "Unable to parse map"));
	if (!check_map_validity(&game, &game.map))
		return (write_error(&game, "Map is not valid"));
	if (game.player.pos.x == -1 || game.player.pos.y == -1)
		return (write_error(&game, "Bad player position"));
	if (!init_mlx(&game))
		return (write_error(&game, "Unable to initialize mlx"));
}
