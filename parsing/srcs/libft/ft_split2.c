/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 12:23:42 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/09 18:14:24 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

static int      words_n2(const char *s, char c)
{
    int count;
    int i;
	int	dquote;

    i = 0;
	dquote = 2;
	count = 0;
    while (s[i])
    {    
		if (is_dquote(s[i]))
			dquote++;
		if (s[i] != c && (s[i + 1] == c || !s[i + 1]) && (dquote % 2 == 0))
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
		  i++;
      len++;
    }
    return (len);
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
