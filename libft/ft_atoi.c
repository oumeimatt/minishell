/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 19:08:50 by oel-yous          #+#    #+#             */
/*   Updated: 2021/09/04 14:36:28 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


long		ft_atoi(char *str)
{
	int				signe;
	unsigned long long	r;

	while (*str >= 9 && *str <= 32)
		str++;
	signe = 1;
	if (*str == '-')
	{
		signe = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	r = 0;
	while (*str >= 48 && *str <= 57)
	{
		r = r * 10 + *str - '0';
		if ((unsigned long long )r > 9223372036854775808U)
			return ((signe < 0) ? 0 : -1);
		str++;
	}
	r = r * signe;
	return (r);
}
