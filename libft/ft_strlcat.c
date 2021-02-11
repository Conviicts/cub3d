/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 21:57:43 by jode-vri          #+#    #+#             */
/*   Updated: 2021/01/26 10:16:35 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	len;

	len = ft_strlen(dst);
	if (len > dstsize)
		return (dstsize + ft_strlen(src));
	return (ft_strlcpy(dst + len, src, dstsize - len) + len);
}
