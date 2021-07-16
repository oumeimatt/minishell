/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 16:52:50 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/16 15:07:39 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	norme1_parser_tab_checker(t_lstredir **tmp,
char **tab, int i, int **flag)
{
	if (!ft_strcmp(tab[i], "<"))
		lstredir_addback(tmp, lstredir_new(1, tab[i + 1]));
	else if (!ft_strcmp(tab[i], "<<"))
		lstredir_addback(tmp, lstredir_new(2, tab[i + 1]));
	**flag = 2;
}

static void	norme2_parser_tab_checker(t_lstredir **tmp,
char **tab, int i, int **flag)
{
	if (!ft_strcmp(tab[i], ">"))
		lstredir_addback(tmp, lstredir_new(3, tab[i + 1]));
	if (!ft_strcmp(tab[i], ">>"))
		lstredir_addback(tmp, lstredir_new(4, tab[i + 1]));
	**flag = 2;
}

void	norme5_parser_tab_checker(t_iofiles *iofiles,
t_lstredir *tmp, int j)
{
	iofiles->tokens[j] = NULL;
	iofiles->redir = tmp;
}

int	norme6_parser_tab_checker(char **tab,
int i, t_lstredir **tmp, int *flag)
{
	if (!ft_strcmp(tab[i], "<") || !ft_strcmp(tab[i], "<<"))
	{
		norme1_parser_tab_checker(tmp, tab, i, &flag);
		return (1);
	}
	else if (!ft_strcmp(tab[i], ">") || !ft_strcmp(tab[i], ">>"))
	{
		norme2_parser_tab_checker(tmp, tab, i, &flag);
		return (1);
	}
	return (0);
}
