/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 18:37:15 by jode-vri          #+#    #+#             */
/*   Updated: 2021/01/27 16:35:30 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	free_map(t_game *game)
{
	int		i;

	i = -1;
	if (game->map.map != NULL)
	{
		while (++i < game->map.height)
		{
			if (game->map.map[i] != NULL)
				free(game->map.map[i]);
		}
	}
	if (game->gnl_tmp)
		free(game->gnl_tmp);
	free(game->gnl_line);
	free(game->map.map);
}

void	free_image(t_game *game, t_xpm *xpm)
{
	if (xpm->path != NULL)
	{
		free(xpm->path);
		if (xpm->img.ptr != NULL)
			mlx_destroy_image(game->window.mlx, xpm->img.ptr);
	}
}

void	clean_game(t_game *game)
{
	if (game->map.map != NULL)
		free_map(game);
	if (game->draw.buffer != NULL)
		free(game->draw.buffer);
	if (game->sprites != NULL)
		free(game->sprites);
	free_image(game, &(game->texture.north));
	free_image(game, &(game->texture.south));
	free_image(game, &(game->texture.east));
	free_image(game, &(game->texture.west));
	free_image(game, &(game->texture.sprite));
	if (game->img.ptr != NULL)
		mlx_destroy_image(game->window.mlx, game->img.ptr);
	if (game->window.win != NULL)
		mlx_destroy_window(game->window.mlx, game->window.win);
	if (game->window.mlx != NULL)
	{
		mlx_destroy_display(game->window.mlx);
		free(game->window.mlx);
	}
	if (game->fd != -1)
		close(game->fd);
}

int		close_game(t_game *game)
{
	clean_game(game);
	exit(EXIT_SUCCESS);
	return (0);
}

int		game_loop(t_game *game)
{
	raycasting(game);
	move_player(game);
	return (0);
}
