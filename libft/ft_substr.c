/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:30:18 by oel-yous          #+#    #+#             */
/*   Updated: 2021/09/04 15:10:29 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newstr;
	size_t	i;

	i = 0;
	newstr = (char *)malloc(sizeof(char) * (len + 1));
	if (newstr == NULL)
		return (NULL);
	while (s[i] && len > i)
	{
		newstr[i] = s[start];
		i++;
		start++;
	}
	newstr[i] = '\0';
	return (newstr);
}
