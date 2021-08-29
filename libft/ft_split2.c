/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 12:23:42 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/16 19:56:21 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		export2_words_n2(const char *s, char c, int i, int *count)
{
	int dquote;

	dquote = 2;
//	printf ("export wordsn2 done0,0		%s, {%c}		%d	%d\n", s, c, i, *count);
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
		if (s[i])	
			i++;
	}
//	printf ("export wordsn2 done0,1		%s, {%c}		%d	%d\n", s, c, i, *count);
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

//	printf ("wordsn3 done0,0\n");
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
//	printf ("wordsn3 done0,0\n");
	return (count);
}

static int      word_len2(char *str, unsigned int index, char delim)
{
	int len;
	int i;
	
	len = 0;
	i = index;
//	printf("wordslen2 done0.0	%s,	%d,%d\n", str, i, len);
	while (str[i] != '\0' && str[i] != delim) 
	{
		if (is_dquote(str[i]))
		{
			while (str[++i] && !is_dquote(str[i]))
				len++;
			len++;
		}
		else if (is_squote(str[i]))
		{
			while (str[++i] && !is_squote(str[i]))
				len++;
			len++;
		}
		i++;
		len++;
	}
//	printf("wordslen2 done0.1	%s,	%d,%d\n", str, i, len);
	return (len);
	/*	echo '$HOME' */
}


char            **ft_split2(const char *str, char c)
{
	char    **tab;
	int     i;
	int     j;

	if (str)
	{
//		printf ("ftsplit2 0,0	%s,%c\n", str, c);
		if (!(tab = (char **)malloc(sizeof(char *) * (words_n2((char *)str, c) + 1))))
			return (0);
		i = 0;
		j = 0;
		while (i < words_n2((char *)str, c))
		{
			while (str[j] == c)
				j++;
			if (!(tab[i] = ft_substr(str, j, word_len2((char *)str, j , c))))
				return (free_tab(tab, i - 1));
			j += word_len2((char *)str, j, c) + 1;
			i++;
		}
		tab[i] = 0;
//		printf ("ftsplit2 0,1	%s,%c	%s\n", str, c, tab[0]);
		return (tab);
	}
	return (0);
}