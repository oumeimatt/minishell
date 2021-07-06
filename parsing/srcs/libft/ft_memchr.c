/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 17:52:30 by oel-yous          #+#    #+#             */
/*   Updated: 2021/06/11 16:56:16 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	val;
	size_t			i;

	i = 0;
	val = (unsigned char)c;
	str = (unsigned char*)s;
	while (--n > 0)
	{
		if (str[i] == val)
			return (str + i);
		i++;
	}
	return (NULL);
}
