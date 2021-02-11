/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 15:29:58 by jode-vri          #+#    #+#             */
/*   Updated: 2021/01/27 15:01:11 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	check_args(t_game *game, int ac, char **av)
{
	if (ac >= 2)
	{
		if (ac > 3)
			return (write_error(game, TMA));
		game->map.map_path = av[1];
		if (ac == 3)
		{
			if (ft_strncmp(av[2], "--save", ft_strlen(av[2])) == 0)
				game->save = 1;
			else
				return (write_error(game, WA));
		}
		else
			game->save = 0;
		return (1);
	}
	else
		return (write_error(game, NEA));
}
