/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 17:34:09 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/10 19:38:52 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void			tab_trimmer(char **tab)
{
	int 	i;

	i = 0;
	while (tab[i])
	{
		tab[i] = ft_strtrim(tab[i], "\"\' \t");
		i++;
	}		
}

int			max_v(int a, int b)
{
	return ((a > b ? a : b));
}

int			min_v(int a, int b)
{
	return ((a < b ? a : b));
}

void			destroy_tab(char **tab)
{
	int i;
	int j;

	i = 0;
	j = tab_len(tab);
	while (i < j)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
