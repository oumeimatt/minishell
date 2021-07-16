/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 18:29:55 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/16 19:45:35 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int      words_n(const char *s, char c)
{
	int count;
	int i;
	int dquote;
	int squote;

	i = 0;
	count = 0;
	dquote = 2;
	squote = 2;
	if (!ft_strncmp(s, "export", 6))
	{
		while (s[i])
		{
			if ((s[i] != c) && (s[i + 1] == c || !s[i + 1]))
				count++;
			if (is_dquote(s[i]) || is_squote(s[i]))
			{
				char tmp = s[i];
				while (s[i] != '\0')
				{
					if (s[i + 1] == tmp)
						dquote = 4;
					if ((s[i] != c) && (dquote == 4) && (s[i + 1] == c || !s[i + 1]))
						count++;
					i++;
				}
				return (count);
			}
			i++;
		}
	}
	while (s[i])
	{    
	
		if (s[i] != c && (s[i + 1] == c || !s[i + 1]))
			count++;
		i++;
	}
	return (count);
}

int      word_len(const char *str, unsigned int index, char delim)
{
	int len;
	int i;
	int quote;
	
	len = 0;
	quote = 0;
	i = index;
	while (str[i] && str[i] != '\0' && str[i] != delim) 
	{
		if (!ft_strncmp(str, "export", 6))
		{
/* 			if (is_dquote(str[i]) || is_squote(str[i]))
			{
				while (str[i] && str[i] != '\0')
				{
					i++;
					len++;
					if (is_dquote(str[i]) || is_squote(str[i]))
						return (len + 1);
				}
			} */
			while (str[i] != '\0')
			{
				if (str[i] == delim)
					return (len);
				if (is_dquote(str[i]) || is_squote(str[i]))
				{
					char tmp = str[i];
					i++;
					while (str[i] != '\0')
					{
						if (tmp == str[i] && str[i + 1] == delim)
							return (len);
						i++;
						len++;
					}
				}
				i++;
				len++;
			}
		}
		i++;
		len++;
	}
	return (len);
}

int		is_dollar(char c)
{
	if (c == '$')
		return (1);
	return (0);
}

int		is_squote(char c)
{
	if (c == 39)
		return (1);
	return (0);
}

int     is_dquote(char c)
{
	if (c == '"')
		return (1);
	return (0);
}

char	**free_tab(char **tab, size_t filled_elems)
{
	size_t     i;

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

char            **ft_split(const char *str, char c)
{
	char    **tab;
	int     i;
	int     j;

	if (str)
	{
		if (!(tab = (char **)malloc(sizeof(char *) * (words_n(str, c) + 1))))
			return (0);
		i = 0;
		j = 0;
		while (i < words_n(str, c))
		{
			while (str[j] == c)
				j++;
			if (!(tab[i] = ft_substr(str, j, word_len(str, j , c))))
				return (free_tab(tab, i - 1));
			j += word_len(str, j, c);
			i++;
		}
		tab[i] = 0;
		return (tab);
	}
	return (0);
}