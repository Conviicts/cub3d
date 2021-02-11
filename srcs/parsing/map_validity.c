/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 17:58:06 by jode-vri          #+#    #+#             */
/*   Updated: 2021/01/27 15:02:25 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	check_map_validity_two(t_map *map, t_ipos p, int l, int tmp)
{
	if (!ft_is_in_charset(map->map[p.x][p.y], " 012NSEW"))
		return (0);
	if (map->map[p.x][0] != '1' || map->map[p.x][l - 1] != '1')
		return (0);
	if (p.x != 0 && (int)ft_strlen(map->map[p.x - 1]) < l)
	{
		if (map->map[p.x][ft_strlen(map->map[p.x - 1])] != '1'
			&& map->map[p.x - 1][ft_strlen(map->map[p.x - 1])] != '1')
			return (0);
	}
	else if (p.x != 0 && (int)ft_strlen(map->map[p.x - 1]) > l)
	{
		tmp = l - 1;
		while (map->map[p.x - 1][tmp])
		{
			if (map->map[p.x - 1][tmp++] != '1')
				return (0);
		}
	}
	return (1);
}

int	check_first_last_line(t_map *map)
{
	int	i;

	i = -1;
	while (map->map[0][++i])
	{
		if (map->map[0][i] != '1')
			return (0);
	}
	i = -1;
	while (map->map[map->height - 1][++i])
	{
		if (map->map[map->height - 1][i] != '1')
			return (0);
	}
	return (1);
}

int	check_has_player(t_game *game, t_map *map, t_ipos p)
{
	if (game->player.pos.x != -1)
		return (0);
	if (game->player.pos.y != -1)
		return (0);
	game->player.pos.x = p.y + 0.5;
	game->player.pos.y = p.x + 0.5;
	set_orientation(game, map->map[p.x][p.y]);
	map->map[p.x][p.y] = '0';
	return (1);
}

int	check_map_validity(t_game *game, t_map *map)
{
	t_ipos	p;
	int		l;
	int		tmp;

	tmp = 0;
	if (!check_first_last_line(map))
		return (0);
	p.x = -1;
	while (++p.x < map->height)
	{
		p.y = -1;
		l = ft_strlen(map->map[p.x]);
		while (++p.y < l)
		{
			if (ft_is_in_charset(map->map[p.x][p.y], "NSEW"))
				if (!check_has_player(game, map, p))
					return (0);
			if (!check_map_validity_two(map, p, l, tmp))
				return (0);
		}
	}
	return (1);
}
