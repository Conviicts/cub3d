/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 02:27:54 by jode-vri          #+#    #+#             */
/*   Updated: 2021/01/27 15:01:11 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

t_img	create_image(t_game *game)
{
	t_img	img;

	img.ptr = NULL;
	img.ptr = mlx_new_image(game->window.mlx, game->window.width,
			game->window.height);
	img.data = (int *)mlx_get_data_addr(img.ptr,
			&img.bpp, &img.size, &img.endian);
	return (img);
}
