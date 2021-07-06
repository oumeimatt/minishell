/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 15:07:57 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/06 12:46:44 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing/inc/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (s2[i] == '\0' && s1[i] != '\0')
		return (1);
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] == s2[i])
		{
			i++;
		}
		if (s1[i] != s2[i])
		{
			return (1);
		}
	}
	return (0);
}


char    *ft_charjoin(char *str, char c)
{
    int l;
    char    *res;
    int i =0;

    l = strlen(str);
    res = malloc(l + 2);
    while (i < l)
    {
        res[i] = *str;
        str++;
        i++;
    }
    res[i] = c;
    res[i + 1] = '\0';
    return(res);
}
