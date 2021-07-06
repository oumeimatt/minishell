/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 11:04:13 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/06 12:42:25 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' || i >= (n - 1))
			return (0);
		i++;
	}
	return (s1[i] - s2[i]);
}

// int		ft_strcmp(const char *s1, const char *s2)
// {
// 	size_t i;

// 	i = 0;
// 	while (s1[i] == s2[i])
// 	{
// 		if (s1[i] == '\0')
// 			return (0);
// 		i++;
// 	}
// 	return (s1[i] - s2[i]);
// }