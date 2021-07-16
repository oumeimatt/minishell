/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 19:27:17 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/16 15:12:36 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	norme3_parser_tab_checker(t_iofiles *iofiles,
char **tab, int i, int *j)
{
	iofiles->tokens[*j] = ft_strdup(tab[i]);
	(*j)++;
}

static void	norme4_parser_tab_checker(int *flag, int *i)
{
	if (*flag >= 1)
		*flag = *flag - 1;
	else if (*flag == 0)
		*flag = 0;
	(*i)++;
}

void	parser_tab_checker(char **tab, t_iofiles *iofiles)
{
	int			i;
	int			j;
	int			flag;
	t_lstredir	*tmp;

	j = 0;
	i = 0;
	flag = 0;
	tmp = malloc(sizeof(t_lstredir));
	tmp = NULL;
	iofiles->tokens = NULL;
	iofiles->tokens = (char **) malloc (sizeof(char *) * 1024);
	iofiles->redir = malloc (sizeof (t_lstredir));
	iofiles->redir = NULL;
	while (tab[i])
	{
		if (flag == 0 && !norme6_parser_tab_checker(tab, i, &tmp, &flag))
			norme3_parser_tab_checker(iofiles, tab, i, &j);
		norme4_parser_tab_checker(&flag, &i);
	}
	norme5_parser_tab_checker(iofiles, tmp, j);
}
