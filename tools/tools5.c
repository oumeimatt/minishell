/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:56:21 by ztaouil           #+#    #+#             */
/*   Updated: 2021/09/04 19:24:53 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

void	tab_trimmer(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		tab[i] = purge_quotes(tab[i]);
		i++;
	}
}

int	spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
