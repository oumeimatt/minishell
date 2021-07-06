/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 18:19:48 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/06 18:20:08 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_word(char const *str, int i, int *nb_word, int c)
{
	*nb_word += 1;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}

int	ft_add_word(char **tab, char const *str, int *nb_word, int c)
{
	int		word_len;
	int		j;
	char	*tmp;
	int		k;

	word_len = 0;
	k = 0;
	while (str[word_len] != c && str[word_len] != '\0')
		word_len++;
	tmp = (char *)malloc((word_len + 1) * sizeof(char));
	tmp[word_len] = '\0';
	j = 0;
	while (k < word_len)
	{
		tmp[j] = str[k++];
		j++;
	}
	tab[*nb_word] = tmp;
	*nb_word += 1;
	return (word_len);
}

void	initial(int *i, int *j)
{
	*i = 0;
	*j = 0;
}

char	**ft_return(char **tab, int number_words)
{
	if (!number_words && !tab)
		return (NULL);
	else
		return (tab);
}

char	**ft_split_2(char const *str, char c)
{
	int		i;
	char	**tab;
	int		number_words;

	initial(&i, &number_words);
	if (!str)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] != c)
			i = ft_word(str, i, &number_words, c);
		else
			i++;
	}
	tab = (char **)malloc((number_words + 1) * sizeof(char *));
	tab[number_words] = 0;
	initial(&i, &number_words);
	while (str[i] != '\0')
	{
		if (str[i] != c)
			i += ft_add_word(tab, str + i, &number_words, c);
		else
			i++;
	}
	return (ft_return(tab, number_words));
}
