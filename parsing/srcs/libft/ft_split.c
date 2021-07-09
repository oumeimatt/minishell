/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 18:29:55 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/09 18:14:07 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

int      words_n(const char *s, char c)
{
	int count;
	int i;
	int quote;

	i = 0;
	count = 0;
	quote = 0;
	while (s[i])
	{    
		if ((is_dquote(s[i]) || is_squote(s[i])) && !quote)
			quote = 1;
		else if ((is_dquote(s[i]) || is_squote(s[i])) && quote)
			quote = 0;		
		if (s[i] != c && (s[i + 1] == c || !s[i + 1]) && !quote)
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
		if (is_dquote(str[i]) || is_squote(str[i]))
		{
			while (str[i] && str[i] != '\0')
			{
				i++;
				len++;
				if (is_dquote(str[i]) || is_squote(str[i]))
					return (len + 1);
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

	str = redirection_reformat(str);
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

char 		*redirection_reformat(const char *string)
{
	char *str;
	int p_count;
	int s_count;
	int quote;

	quote = 0;
	s_count = 0;
	p_count = 0;
	str = (char *)malloc(sizeof(char) * ft_strlen(string) * 10);
	if (!str)
		return (NULL);
	while (string[p_count] != '\0')
	{
		if ((is_dquote(string[p_count]) || is_squote(string[p_count])) && !quote)
			quote = 1;
		else if ((is_dquote(string[p_count]) || is_squote(string[p_count])) && quote)
			quote = 0;
		if (is_redir(string[p_count + 1]) && !is_redir(string[p_count]) && string[p_count] != ' ' && quote == 0)
		{
			str[s_count++] = string[p_count++];
			str[s_count++] = ' ';
		}
		if (is_redir(string[p_count]) && !is_redir(string[p_count + 1]) && quote == 0)
		{
			str[s_count++] = string[p_count++];
			str[s_count++] = ' ';
		}
		str[s_count++] = string[p_count];
		p_count++;
	}
	str[s_count] = '\0';
	return (str);
}

/* char		**split_v3(const char *str, char dim, char **tab)
{
	int p_count;
	int t_count;
	int d_quot;
	int s_quot;

	d_quot =  0;
	s_quot =  0;
	p_count = 0;
	t_count = 0;
	while (str[p_count] != '\0' && str[p_count] != dim)
	{
		

		tab[t_count]
		p_count++;
	}
} */