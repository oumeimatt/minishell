/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:54:29 by oel-yous          #+#    #+#             */
/*   Updated: 2021/06/11 16:56:16 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*ds;
	char	*sr;
	char	temp[len];
	size_t	i;

	ds = (char*)dst;
	sr = (char*)src;
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
