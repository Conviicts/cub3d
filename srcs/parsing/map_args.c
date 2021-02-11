/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 17:34:57 by jode-vri          #+#    #+#             */
/*   Updated: 2021/01/27 15:47:31 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game.h"

int	set_window_resolution(t_game *g, char *line)
{
	line++;
	if (g->window.width != -1 || g->window.height != -1)
		return (write_error(g, "Multiple Resolution field"));
	g->window.width = 0;
	g->window.height = 0;
	while (*line && !ft_isdigit(*line))
		if (*line++ != ' ')
			return (write_error(g, "Bad characters(s) in resolution field"));
	while (*line && ft_isdigit(*line))
		g->window.width = (g->window.width * 10) + (*line++ - '0');
	while (*line && !ft_isdigit(*line))
		if (*line++ != ' ')
			return (write_error(g, "Bad characters(s) in resolution field"));
	while (*line && ft_isdigit(*line))
		g->window.height = (g->window.height * 10) + (*line++ - '0');
	while (*line)
		if (*line++ != ' ')
			return (write_error(g, "Bad characters(s) in resolution field"));
	return (1);
}

int	set_textures(t_game *g, char *line, char **texture, int s)
{
	int		i;

	if (*texture != NULL)
		return (write_error(g, "Multiple texture field"));
	line += s;
	*texture = malloc(sizeof(char) * ft_strlen(line) + 1);
	if (*texture == NULL)
		return (write_error(g, "Unable to malloc for texture path"));
	while (*line && *line == ' ')
		line++;
	i = -1;
	while (*line && (*line >= 46 && *line < 123))
		(*texture)[++i] = *line++;
	while (*line)
	{
		if (*line != ' ')
			return (write_error(g, "Bad characters(s) in texture field"));
		line++;
	}
	(*texture)[++i] = 0;
	return (1);
}

int	check_colors(t_game *g, t_color *color)
{
	if (color->is_r == 0 || color->r < 0 || color->r > 255)
		return (write_error(g, R_ERROR));
	if (color->is_g == 0 || color->g < 0 || color->g > 255)
		return (write_error(g, G_ERROR));
	if (color->is_b == 0 || color->b < 0 || color->b > 255)
		return (write_error(g, B_ERROR));
	return (1);
}

int	set_colors2(t_game *g, char *line, t_color *color, int count_comma)
{
	while (*line && (*line == ' ' || *line == ','))
		if (*line++ == ',')
			count_comma++;
	while (*line && ft_isdigit(*line))
	{
		color->g = (color->g * 10) + (*line++ - '0');
		color->is_g = 1;
	}
	check_comma(g, count_comma);
	while (*line && (*line == ' ' || *line == ','))
		if (*line++ == ',')
			count_comma++;
	while (*line && ft_isdigit(*line))
	{
		color->b = (color->b * 10) + (*line++ - '0');
		color->is_b = 1;
	}
	check_comma(g, count_comma);
	while (*line && (*line == ' ' || *line == ','))
		if (*line++ == ',')
			count_comma++;
	check_comma(g, count_comma);
	return (1);
}

int	set_colors(t_game *g, char *line, t_color *color)
{
	int count_comma;
	int i;

	count_comma = 0;
	i = -1;
	line++;
	if (color->is_r != 0 || color->is_g != 0 || color->is_b != 0)
		return (write_error(g, "Multiple color field"));
	ft_bzero(color, sizeof(t_color));
	while (line[++i])
		if (!ft_is_in_charset(line[i], " ,0123456789"))
			return (write_error(g, BCC_ERROR));
	while (*line && (*line == ' ' || *line == ','))
		if (*line++ == ',')
			count_comma++;
	while (*line && ft_isdigit(*line))
	{
		color->r = (color->r * 10) + (*line++ - '0');
		color->is_r = 1;
	}
	check_comma(g, count_comma);
	set_colors2(g, line, color, count_comma);
	check_colors(g, color);
	return (1);
}
