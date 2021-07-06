/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 17:34:09 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/06 15:20:04 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

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
	j = GetTabSize(tab);
	while (i < j)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void			ft_env_var(t_wrapper *wrp ,char **tab, int i, int start)
{
	int	len;
	char *first;
	
	len = ft_strlen(tab[i]) - start;
	first = ft_substr(tab[i], 0, start);
	printf("keeey ===== %s\n", ft_substr(tab[i], start + 1, len - 1));
	tab[i] = print_value(wrp->env, ft_substr(tab[i], start + 1, len - 1));/* ft_lstgetvalue(wrp->envlst, ft_substr(tab[i], start + 1, len - 1)); */
	if (tab[i] == NULL)
		tab[i] = ft_strdup("");
	tab[i] = ft_strjoin(first, tab[i]);
	free(first);
}

void		tab_checker(t_wrapper *wrp, char **tab, t_iofiles *iofiles)
{
	int	i;
	int flag;
	char *dsign;
	int	start;

	flag = 0;
	i = 0;
	
	while (tab[i])
	{
		if (!ft_strcmp(tab[i] , "<") || !ft_strcmp(tab[i], "<<"))
		{
			iofiles->infile = malloc (sizeof(char *) * 3);
			iofiles->infile[0] = tab[i];
			iofiles->infile[1] = tab[i + 1];
			iofiles->infile[2] = NULL;
		}	
		if (is_squote(tab[i][0]))
			flag = 1;
		if (ft_strchr(tab[i], '$'))
		{
			tab_trimmer(tab);
			dsign = ft_strchr(tab[i], '$');
			start = dsign - tab[i];
			if (flag == 0)	
				ft_env_var(wrp, tab, i, start);
		}
		i++;
	}
}

