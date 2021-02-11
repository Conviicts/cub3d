/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 12:13:30 by jode-vri          #+#    #+#             */
/*   Updated: 2021/01/26 10:16:35 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static void	ft_free(char **dest, int count)
{
	while (count >= 0)
	{
		free(dest[count]);
		dest[count] = 0;
		count--;
	}
	free(dest);
	dest = 0;
}

static int	word_size(char *s, char c, int i)
{
	int j;

	j = 0;
	while (s[i + j] != 0 && s[i + j] != c)
		j++;
	return (j);
}

static char	**malloc_word(char *s, char c, char **dest, int *i)
{
	while (s[i[0]] && ++i[2] >= -5)
	{
		while (s[i[0]] == c && s[i[0]] != 0)
			i[0]++;
		if (s[i[0]] == 0)
			dest[i[2]] = 0;
		if (s[i[0]] == 0)
			return (dest);
		if (!(dest[i[2]] =
		malloc((word_size(s, c, i[0]) + 1) * sizeof(char))))
		{
			ft_free(dest, i[2]);
			return (0);
		}
		i[1] = 0;
		while (s[i[0]] != c && s[i[0]] != 0)
		{
			dest[i[2]][i[1]] = s[i[0]];
			i[0]++;
			i[1]++;
		}
		dest[i[2]][i[1]] = 0;
	}
	dest[i[2] + 1] = 0;
	return (dest);
}

static int	count_words(char *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			return (count);
		count++;
		while (s[i] != c && s[i] != 0)
			i++;
	}
	return (count);
}

char		**ft_split(char *s, char c)
{
	char	**dest;
	int		w_count;
	int		i[3];

	i[0] = 0;
	i[1] = -1;
	if (!s)
		return (0);
	w_count = count_words((char *)s, c);
	i[2] = -1;
	if (!(dest = malloc((w_count + 1) * sizeof(char *))))
		return (0);
	dest = malloc_word((char *)s, c, dest, i);
	return (dest);
}
