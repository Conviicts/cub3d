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
	game->img.ptr = NULL;
	game->window.win = NULL;
	game->window.mlx = NULL;
	game->img.data = NULL;
	game->fd = -1;
}

int		main(int ac, char **av)
{
	t_game	game;

	game.error = NULL;
	setup_game(&game);
	init_game(&game);
	check_args(&game, ac, av);
	if (!init_map(&game))
		return (write_error(&game, ""));
	init_player(&game, &game.player);
	if (!parse_map(&game))
		return (write_error(&game, "Unable to parse map"));
	if (!check_map_validity(&game, &game.map))
		return (write_error(&game, "Map is not valid"));
	if (game.player.pos.x == -1 || game.player.pos.y == -1)
		return (write_error(&game, "Bad player position"));
	if (!init_mlx(&game))
		return (write_error(&game, "Unable to initialize mlx"));
}
