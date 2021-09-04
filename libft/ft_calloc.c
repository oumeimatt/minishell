/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 15:52:56 by oel-yous          #+#    #+#             */
/*   Updated: 2021/09/04 14:50:03 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*res;
	size_t	i;

	i = 0;
	res = (char *)malloc(size * count);
	while (i < count)
	{
		res[i] = 0;
		i++;
	}
	return (res);
}
