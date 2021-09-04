/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:54:29 by oel-yous          #+#    #+#             */
/*   Updated: 2021/09/04 14:56:46 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*ds;
	char	*sr;
	char	temp[1000];
	size_t	i;

	ds = (char *)dst;
	sr = (char *)src;
	i = 0;
	while (i < len)
	{
		temp[i] = sr[i];
		i++;
	}
	i = 0;
	while (i < len)
	{
		ds[i] = temp[i];
		i++;
	}
	return (dst);
}
