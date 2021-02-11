/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 21:07:19 by jode-vri          #+#    #+#             */
/*   Updated: 2021/01/27 15:01:11 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	rgb_to_decimal(t_color color)
{
	return ((color.r * 65536) + (color.g * 256) + color.b);
}

int	check_vars(t_game *g)
{
	if (g->window.width == -1 || g->window.height == -1)
		return (write_error(g, "[PARSING] - Missing resolution field"));
	if (g->texture.north.path == NULL)
		return (write_error(g, "[PARSING] - Missing North texture field"));
	if (g->texture.south.path == NULL)
		return (write_error(g, "[PARSING] - Missing South texture field"));
	if (g->texture.west.path == NULL)
		return (write_error(g, "[PARSING] - Missing West texture field"));
	if (g->texture.east.path == NULL)
		return (write_error(g, "[PARSING] - Missing East texture field"));
	if (g->texture.sprite.path == NULL)
		return (write_error(g, "[PARSING] - Missing sprite texture field"));
	if (g->texture.ceiling.r == -1 || g->texture.ceiling.g == -1
		|| g->texture.ceiling.b == -1)
		return (write_error(g, "[PARSING] - Missing ceiling color field"));
	if (g->texture.floor.r == -1 || g->texture.floor.g == -1
		|| g->texture.floor.b == -1)
		return (write_error(g, "[PARSING] - Missing floor texture field"));
	return (1);
}

int	check_comma(t_game *g, int nb)
{
	if (nb > 2)
		return (write_error(g, BCC_ERROR));
	return (1);
}
