/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 10:56:52 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/16 16:54:09 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int		ft_set(char c, const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char			*ft_strtrim(char const *s1, const char *set)
{
	size_t begin;
	size_t end;
	size_t len;
	begin = 0;

	if (set == NULL)
		return ((char*)s1);
	
	while (s1[begin] != '\0' && ft_set(s1[begin], set))
		begin++;
	end = ft_strlen((char*)s1);
	while (begin < end && ft_set(s1[end - 1], set))
		end--;
	len = end - begin;
	char *s2 = ft_substr(s1, begin, len);
	if (!s2)
		return (NULL);
	return (s2);
}