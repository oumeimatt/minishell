/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:30:18 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/16 17:36:58 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newstr;
	size_t	i;

//	printf("ftsubstr done0,0\n");
	i = 0;
	newstr = (char*)malloc(sizeof(char) * (len + 1));
	if (newstr == NULL)
		return (NULL);
	while (s[i] && len > i)
	{
		newstr[i] = s[start];
		i++;
		start++;
	}
	newstr[i] = '\0';
//	printf("ftsubstr done0,1\n");
	return (newstr);
}
