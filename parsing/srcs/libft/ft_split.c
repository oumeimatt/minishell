/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 18:29:55 by ztaouil           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/07/08 17:19:05 by ztaouil          ###   ########.fr       */
=======
/*   Updated: 2021/07/08 21:12:25 by ztaouil          ###   ########.fr       */
>>>>>>> exec
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

int      words_n(const char *s, char c)
{
    int count;
    int i;
//	int	dquote;

    i = 0;
//	dquote = 0;
	count = 0;
    while (s[i])
    {    
/* 		if (is_dquote(s[i]))
			dquote++; */
		if (s[i] != c && (s[i + 1] == c || !s[i + 1]) /* && (dquote % 2 == 0) */)
            count++;
		if (is_redir(s[i]) && !(s[i + 1] == ' '))
		{	
			if (is_redir(s[i + 1]) && s[i + 2])
				i++;
			count++;
		}
		i++;
    }
    return (count);
}

int      word_len(const char *str, unsigned int index, char delim)
{
    int len;
    int i;
	
    len = 0;
    i = index;
    while (str[i] && str[i] != delim) 
    {
/*         if (is_dquote(str[i]))
		{
			while (str[i++] && (!is_dquote(str[i])))
				len++;
			return (len + 2);
		} */
		if (is_redir(str[i]))
		{
			if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
				return (2);
			else if ((str[i] == '<' && str[i + 1]) || (str[i] == '>' && str[i + 1]))
				return (1);
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
