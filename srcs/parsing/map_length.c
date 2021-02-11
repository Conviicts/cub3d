/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_length.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 16:42:34 by jode-vri          #+#    #+#             */
/*   Updated: 2021/01/27 15:01:11 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	ft_skip_args(char *line)
{
	while (*line && *line == ' ')
		line++;
	if (!ft_strncmp(line, "R", 1))
		return (1);
	else if (!ft_strncmp(line, "NO", 2))
		return (1);
	else if (!ft_strncmp(line, "SO", 2))
		return (1);
	else if (!ft_strncmp(line, "WE", 2))
		return (1);
	else if (!ft_strncmp(line, "EA", 2))
		return (1);
	else if (!ft_strncmp(line, "S", 1))
		return (1);
	else if (!ft_strncmp(line, "F", 1))
		return (1);
	else if (!ft_strncmp(line, "C", 1))
		return (1);
	return (-1);
}

int	get_map_length(t_game *game, char *name)
{
	int		fd;
	int		ret;
	int		count;

	count = 0;
	game->gnl_line = NULL;
	fd = open(name, O_RDONLY);
	if (fd == -1)
		return (-1);
	ret = get_next_line(fd, &game->gnl_line, game);
	while (ret != -1)
	{
		if (game->gnl_line && *game->gnl_line != '\0')
		{
			ret = ft_skip_args(game->gnl_line);
			if (ret == -1)
				count++;
		}
		free(game->gnl_line);
		if (ret == 0)
			break ;
		ret = get_next_line(fd, &game->gnl_line, game);
	}
	close(fd);
	return (count);
}
