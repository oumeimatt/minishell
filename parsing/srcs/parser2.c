/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 19:27:17 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/10 21:12:56 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void		tab_checker(t_wrapper *wrp, char **tab, t_iofiles *iofiles)
{
	int	i;
	int	j;
	int flag;
	t_lstredir *tmp;

	j = 0;
	i = 0;
	flag = 0;
	(void)wrp;
	tmp = NULL;
	iofiles->tokens = NULL;
	iofiles->redir = NULL;
	iofiles->redir = malloc (sizeof (t_lstredir));
	iofiles->tokens = (char **) malloc (sizeof(char *) * 1024);
	
	while (tab[i])
	{
		if (!ft_strcmp(tab[i] , "<") || !ft_strcmp(tab[i], "<<"))
		{
			if (!ft_strcmp(tab[i], "<"))	
				lstredir_addback(&tmp, lstredir_new(1, tab[i + 1]));
			else if (!ft_strcmp(tab[i], "<<"))
				lstredir_addback(&tmp, lstredir_new(2, tab[i + 1]));
			flag = 2;
		}	
		else if (!ft_strcmp(tab[i], ">") || !ft_strcmp(tab[i], ">>"))
		{
			if (!ft_strcmp(tab[i], ">"))
				lstredir_addback(&tmp, lstredir_new(3, tab[i + 1]));
			if (!ft_strcmp(tab[i], ">>"))
				lstredir_addback(&tmp, lstredir_new(4, tab[i + 1]));
			flag = 2;
		}
		else if (flag == 0)
		{
			fill_tokens(iofiles, tab, &i, &j);
		}
		flag = (flag > 0 ? flag - 1 : 0);
		i++;
	}
	iofiles->tokens[j] = NULL;
	iofiles->redir = tmp;
}

void		fill_tokens(t_iofiles *iofiles, char **tab, int *i, int *j)
{
	iofiles->tokens[*j] = ft_strdup(tab[*i]);
	*j += 1;	
}