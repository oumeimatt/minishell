/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 10:31:23 by oel-yous          #+#    #+#             */
/*   Updated: 2021/06/11 16:56:16 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	ch;
	unsigned char	*str;

	i = 0;
	ch = (char)c;
	str = (unsigned char *)s;
	while (*str)
	{
		if (*str == ch)
			return ((char *)(str + i));
		str++;
	}
	if (ch == '\0')
		return ((char *)str);
	return (NULL);
}
