/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 18:29:55 by ztaouil           #+#    #+#             */
/*   Updated: 2021/09/04 15:04:28 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	words_n(const char *s, char c)
{
	int	count;
	int	i;
	int	*dq;
	int	*sq;

	dq = ext_dsqmsk(s, 1);
	sq = ext_dsqmsk(s, 0);
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && ((s[i + 1] == c && dq[i + 1] == 0 && sq[i + 1] == 0)
				|| !s[i + 1]))
			count++;
		i++;
	}
	free(dq);
	free(sq);
	return (count);
}

static int	word_len(const char *str, unsigned int index, char delim)
{
	int	len;
	int	i;
	int	*dq;
	int	*sq;

	dq = ext_dsqmsk(str, 1);
	sq = ext_dsqmsk(str, 0);
	len = 0;
	i = index;
	while (str[i] && str[i] != '\0' && (str[i] != delim
			|| (dq[i] == 1 || sq[i] == 1)))
	{
		if (str[i])
			i++;
		len++;
	}
	free(dq);
	free(sq);
	return (len);
}

static char	**free_tab(char **tab, size_t filled_elems)
{
	size_t	i;

	i = 0;
	while (i < filled_elems)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	return (0);
}

char	**ft_split(const char *str, char c)
{
	char	**tab;
	int		i;
	int		j;

	if (str)
	{
		tab = (char **)malloc(sizeof(char *) * (words_n(str, c) + 1));
		if (!tab)
			return (0);
		i = 0;
		j = 0;
		while (i < words_n(str, c))
		{
			while (str[j] == c)
				j++;
			tab[i] = ft_substr(str, j, word_len(str, j, c));
			if (!tab)
				return (free_tab(tab, i - 1));
			j += word_len(str, j, c);
			i++;
		}
		tab[i] = 0;
		return (tab);
	}
	return (0);
}
