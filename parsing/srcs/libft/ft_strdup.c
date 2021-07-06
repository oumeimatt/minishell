/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:32:37 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/06 12:56:07 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		length;
	char	*temp;

	length = 0;
	while (s1[length] != '\0')
		length++;
	if (!s1)
		return (NULL);
	temp = (char *)malloc(sizeof(char) * (length + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		temp[i] = (char)s1[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
