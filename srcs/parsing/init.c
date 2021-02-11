/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 15:19:05 by jode-vri          #+#    #+#             */
/*   Updated: 2021/01/27 15:01:11 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int		init_map(t_game *game)
{
	int	map_len;

	map_len = ft_strlen(game->map.map_path);
	if (ft_strncmp(game->map.map_path + map_len - 4, ".cub", 4) != 0
		|| map_len <= 4)
	{
		game->error = "[PARSING] Map file does not have .cub extension";
		return (0);
	}
	game->fd = open(game->map.map_path, O_RDONLY);
	if (game->fd == -1)
	{
		game->error = "[PARSING] Unable to open map file";
		return (0);
	}
	return (1);
}
