/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 06:20:05 by jode-vri          #+#    #+#             */
/*   Updated: 2021/01/27 15:01:11 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	draw_bmp_header(t_game *g, int fd)
{
	int	tmp;

	write(fd, "BM", 2);
	tmp = 14 + 40 + 4 * g->window.width * g->window.height;
	write(fd, &tmp, 4);
	tmp = 0;
	write(fd, &tmp, 2);
	write(fd, &tmp, 2);
	tmp = 54;
	write(fd, &tmp, 4);
	tmp = 40;
	write(fd, &tmp, 4);
	write(fd, &g->window.width, 4);
	write(fd, &g->window.height, 4);
	tmp = 1;
	write(fd, &tmp, 2);
	write(fd, &g->img.bpp, 2);
	tmp = 0;
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
}

void	draw_bmp(t_game *game)
{
	int fd;
	int y;
	int x;

	if ((fd = open("image.bmp", O_CREAT | O_WRONLY, S_IRWXU)) == -1)
		write_error(game, "Unable to create bmp image\n");
	draw_bmp_header(game, fd);
	y = game->window.height;
	while (y >= 0)
	{
		x = -1;
		while (++x < game->window.width)
			write(fd, &game->img.data[y * game->img.size / 4 + x], 4);
		y--;
	}
	close(fd);
	close_game(game);
}
