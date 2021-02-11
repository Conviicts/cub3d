/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 15:25:28 by jode-vri          #+#    #+#             */
/*   Updated: 2021/01/27 15:01:11 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	write_error(t_game *game, char *error)
{
	ft_putstr_fd("Error\n", 1);
	if (game->error != NULL)
		ft_putstr_fd(game->error, 1);
	else
		ft_putstr_fd(error, 1);
	ft_putchar_fd('\n', 1);
	close_game(game);
	return (1);
}
