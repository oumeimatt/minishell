/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 19:09:59 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/10 19:38:52 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		tab_len(char **tab)
{
	int i;

	i = 0;
	if (tab)
	{
		while (tab[i] != NULL)
			i++;
	}
	return (i);
}

int		exists_in_tab(char *s, char **tab)
{
	while (*tab)
	{
		if (!ft_strncmp(s, *tab, max_v(ft_strlen(s), ft_strlen(*tab))))
			return (1);
		tab++;
	}
	return (0);
}

int		index_of_in_tab(char *s, char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if (!ft_strncmp(s, tab[i], max_v(ft_strlen(s), ft_strlen(tab[i]))))
			return (i);
		i++;
	}
	return (-1);
}

int		free_s_tab(char **tab)
{
	int		i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			if (tab[i])
				free(tab[i]);
			i++;
		}
		free(tab);
	}
	return (0);
}

char	**fix_tmp(char **tmp)
{
	if (ft_strcmp(tmp[0], "export"))
		return (tmp);
	else
	{
		char **tmp2 = (char **)malloc(sizeof(char *) * 3);
		tmp2[0] = ft_strdup("export");
		tmp2[1] = ft_strdup(tmp[1]);
		for (int i = 2; i < tab_len(tmp); i++)
		{	
			tmp2[1] = ft_strjoin(tmp2[1], ft_strdup(" "));
			tmp2[1] = ft_strjoin(tmp2[1], tmp[i]);
		}
		return (tmp2);
	}
}