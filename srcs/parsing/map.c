/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 16:21:39 by jode-vri          #+#    #+#             */
/*   Updated: 2021/01/27 16:17:33 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	ft_parse_map_line(t_game *game, char *line)
{
	while (*line && *line == ' ')
		line++;
	if (!ft_strncmp(line, "R", 1))
		return (set_window_resolution(game, line));
	else if (!ft_strncmp(line, "NO", 2))
		return (set_textures(game, line, &(game->texture.north.path), 2));
	else if (!ft_strncmp(line, "SO", 2))
		return (set_textures(game, line, &(game->texture.south.path), 2));
	else if (!ft_strncmp(line, "WE", 2))
		return (set_textures(game, line, &(game->texture.west.path), 2));
	else if (!ft_strncmp(line, "EA", 2))
		return (set_textures(game, line, &(game->texture.east.path), 2));
	else if (!ft_strncmp(line, "S", 1))
		return (set_textures(game, line, &(game->texture.sprite.path), 1));
	else if (!ft_strncmp(line, "F", 1))
		return (set_colors(game, line, &(game->texture.floor)));
	else if (!ft_strncmp(line, "C", 1))
		return (set_colors(game, line, &(game->texture.ceiling)));
	return (-1);
}

int	stock_line(t_map *map, int i, char *line)
{
	int	j;

	map->map[i] = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (map->map[i] == NULL)
		return (0);
	j = -1;
	while (line[++j])
	{
		if (line[j] == ' ')
			map->map[i][j] = '1';
		else
			map->map[i][j] = line[j];
	}
	map->map[i][j] = '\0';
	return (1);
}

int	process_line(t_game *game, char *line, int *i)
{
	int	res;

	if (*line == '\0' && game->map.map[0] != NULL &&
		game->map.map[game->map.height - 1] == NULL)
		return (write_error(game, "[PARSING] - Empty line in map file"));
	if (*line && *line != '\0')
	{
		res = ft_parse_map_line(game, line);
		if (res == -1)
		{
			if (!check_vars(game))
				return (0);
			if (!stock_line(&game->map, ++(*i), line))
				return (0);
		}
		else if (res == 0)
			return (0);
	}
	return (1);
}

int	malloc_map(t_game *game)
{
	int	count;
	int i;

	i = -1;
	count = get_map_length(game, game->map.map_path);
	if (count == -1 || count == 0)
		return (write_error(game, "[PARSING] - Empty map"));
	game->map.height = count;
	game->map.map = malloc(sizeof(char *) * count);
	if (game->map.map == NULL)
		return (0);
	while (++i < game->map.height)
		game->map.map[i] = NULL;
	return (1);
}

int	parse_map(t_game *game)
{
	int		ret;
	int		i;
	int		j;

	i = -1;
	game->gnl_line = NULL;
	j = malloc_map(game);
	if (!j)
		return (0);
	ret = get_next_line(game->fd, &game->gnl_line, game);
	while (ret != -1)
	{
		if (process_line(game, game->gnl_line, &i) == 0)
		{
			free(game->gnl_line);
			return (0);
		}
		free(game->gnl_line);
		game->gnl_line = NULL;
		if (ret == 0)
			break ;
		ret = get_next_line(game->fd, &game->gnl_line, game);
	}
	return (1);
}
