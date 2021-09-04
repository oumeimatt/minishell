/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:14:26 by oel-yous          #+#    #+#             */
/*   Updated: 2021/09/04 15:06:19 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dest_len;
	size_t	src_len;

	i = 0;
	j = 0;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen((char *)src);
	if (size <= dest_len)
		return (src_len + size);
	while (dest[i] != '\0' && i < size - 1)
		i++;
	while (src[j] != '\0' && i < size - 1)
	{
		dest[i + j] = src[j];
		j++;
	}
	return (dest_len + src_len);
}
