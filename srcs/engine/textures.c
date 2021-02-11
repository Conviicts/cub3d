/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 22:31:29 by jode-vri          #+#    #+#             */
/*   Updated: 2021/01/27 15:01:11 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int		set_texture(t_game *game, t_xpm *xpm)
{
	xpm->img.ptr = mlx_xpm_file_to_image(game->window.mlx,
			xpm->path, &xpm->width, &xpm->height);
	if (xpm->img.ptr == NULL)
		return (0);
	xpm->img.data = (int *)mlx_get_data_addr(xpm->img.ptr, &xpm->img.bpp,
			&xpm->img.size, &xpm->img.endian);
	return (1);
}

void	init_textures(t_game *game)
{
	if (!(set_texture(game, &game->texture.north)))
		write_error(game, "	Texture: path error on north texture.");
	if (!(set_texture(game, &game->texture.south)))
		write_error(game, "	Texture: path error on south texture.");
	if (!(set_texture(game, &game->texture.west)))
		write_error(game, "	Texture: path error on west texture.");
	if (!(set_texture(game, &game->texture.east)))
		write_error(game, "	Texture: path error on east texture.");
	if (!(set_texture(game, &game->texture.sprite)))
		write_error(game, "	Texture: path error on sprite texture.");
}
