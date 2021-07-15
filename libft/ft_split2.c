/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 12:23:42 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/15 14:43:35 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static void		export2_words_n2(const char *s, char c, int i, int *count)
{
	int dquote;

	dquote = 2;
	while (s[i])
	{
		if ((s[i] != c) && ((s[i + 1] == c) || !s[i + 1]))
			(*count)++;
		if (is_dquote(s[i]) || is_squote(s[i]))
		{
			char tmp = s[i];
			while (s[i] != '\0')
			{
				if (s[i + 1] == tmp)
					dquote = 4;
				if ((s[i] != c) && (dquote == 4) && 
				(s[i + 1] == c || !s[i + 1]))
					(*count)++;
				i++;
			}
		}
		i++;
	}
}

static int 		export_words_n2(const char *s, char c)
{
	int i;
	int dquote;
	int count;
	
	dquote = 2;
	i = 0;
	count = 0;
	export2_words_n2(s, c, i, &count);
	return (count);
}

static int      words_n2(const char *s, char c)
{
	int count;
	int i;
	int	dquote;
	int squote;

	i = 0;
	dquote = 2;
	squote = 2;
	count = 0;
	if (!ft_strncmp(s, "export", 6))
		return (export_words_n2(s, c));
	while (s[i])
	{    
		if (is_dquote(s[i]))
			dquote++;
		else if (is_squote(s[i]))
			squote++;
		if ((s[i] != c) && (s[i + 1] == c || !s[i + 1]) && ((dquote % 2 == 0) && (squote % 2 == 0)))
				count++;
		i++;
	}
	return (count);
}

static int      word_len2(const char *str, unsigned int index, char delim)
{
	int len;
	int i;
	
	len = 0;
	i = index;
	while (str[i] && str[i] != delim) 
	{
		if (is_dquote(str[i]))
			while (str[++i] && !is_dquote(str[i]))
				len++;
		else if (is_squote(str[i]))
			while (str[++i] && !is_squote(str[i]))
				len++;
		i++;
		len++;
	}
	if (str[i] == delim)
		return (len);
	return (len + 2);
}

char            **ft_split2(const char *str, char c)
{
	char    **tab;
	int     i;
	int     j;

	if (str)
	{
		if (!(tab = (char **)malloc(sizeof(char *) * (words_n2(str, c) + 1))))
			return (0);
		i = 0;
		j = 0;
		while (i < words_n2(str, c))
		{
			while (str[j] == c)
				j++;
			if (!(tab[i] = ft_substr(str, j, word_len2(str, j , c))))
				return (free_tab(tab, i - 1));
			j += word_len2(str, j, c) + 1;
			i++;
		}
		tab[i] = 0;
		return (tab);
	}
	return (0);
}
