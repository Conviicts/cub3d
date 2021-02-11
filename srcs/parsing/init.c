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

void	init_game2(t_game *game)
{
	game->texture.floor.is_r = 0;
	game->texture.floor.is_g = 0;
	game->texture.floor.is_b = 0;
	game->texture.ceiling.is_r = 0;
	game->texture.ceiling.is_g = 0;
	game->texture.ceiling.is_b = 0;
	game->texture.floor.r = -1;
	game->texture.floor.g = -1;
	game->texture.floor.b = -1;
	game->texture.ceiling.r = -1;
	game->texture.ceiling.g = -1;
	game->texture.ceiling.b = -1;
	game->draw.buffer = NULL;
	game->sprites = NULL;
	game->draw.hit = 0;
}

void	init_game(t_game *game)
{
	game->img.ptr = NULL;
	game->gnl_tmp = NULL;
	game->window.width = -1;
	game->window.height = -1;
	game->map.map = NULL;
	game->texture.north.path = NULL;
	game->texture.north.img.ptr = NULL;
	game->texture.south.path = NULL;
	game->texture.south.img.ptr = NULL;
	game->texture.west.path = NULL;
	game->texture.west.img.ptr = NULL;
	game->texture.east.path = NULL;
	game->texture.east.img.ptr = NULL;
	game->texture.sprite.path = NULL;
	game->texture.sprite.img.ptr = NULL;
	init_game2(game);
}
