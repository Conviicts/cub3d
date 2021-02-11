/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:45:54 by jode-vri          #+#    #+#             */
/*   Updated: 2021/01/26 10:40:12 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

char	*get_line(char *s)
{
	char	*res;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (!(res = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*get_tmp(char *s)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	if (!(res = malloc(sizeof(char) * (ft_strlen(s) - i + 1))))
		return (NULL);
	i++;
	j = 0;
	while (s && s[i])
		res[j++] = s[i++];
	res[j] = '\0';
	free(s);
	return (res);
}

int		get_next_line(int fd, char **line, t_game *game)
{
	char		*buffer;
	int			ret;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	ret = 1;
	while (!is_end_line(game->gnl_tmp) && ret != 0)
	{
		if ((ret = read(fd, buffer, BUFFER_SIZE)) == -1)
		{
			free(buffer);
			return (-1);
		}
		buffer[ret] = '\0';
		game->gnl_tmp = ft_strjoin(game->gnl_tmp, buffer);
	}
	free(buffer);
	*line = get_line(game->gnl_tmp);
	game->gnl_tmp = get_tmp(game->gnl_tmp);
	return (ret == 0 ? 0 : 1);
}
