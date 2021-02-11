/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 15:32:39 by jode-vri          #+#    #+#             */
/*   Updated: 2020/12/23 15:32:41 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(long n, int base)
{
	long	i;

	i = 0;
	while (n)
	{
		n /= base;
		i++;
	}
	return (i);
}

char		*ft_itoa_base(long n, int base, int maj)
{
	char	*str;
	int		len;
	long	digit;
	char	letter;

	if (!n)
		return (ft_strdup("0"));
	letter = maj ? 'A' : 'a';
	len = ft_len(n, base);
	if (!(str = (char *)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	str[len--] = '\0';
	while (n)
	{
		digit = n % base;
		n /= base;
		str[len--] = (digit < 0xA) ? ('0' + digit) : (letter + digit - 0xA);
	}
	return (str);
}
