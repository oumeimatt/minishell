/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 17:34:09 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/06 20:39:04 by ztaouil          ###   ########.fr       */
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

void			ft_env_var(t_wrapper *wrp, t_iofiles *iofiles, char **tab, int i, int start)
{
	int	len;
	char *first;
	
	len = ft_strlen(tab[i]) - start;
	first = ft_substr(tab[i], 0, start);
	iofiles->tokens[i] = print_value(wrp->env, ft_substr(tab[i], start + 1, len - 1));
	if (tab[i] == NULL)
		tab[i] = ft_strdup("");
	iofiles->tokens[i] = ft_strjoin(first, iofiles->tokens[i]);
	free(first);
}

void		tab_checker(t_wrapper *wrp, char **tab, t_iofiles *iofiles)
{
	int	i;
	int	j;
	int flag;

	j = 0;
	i = 0;
	flag = 0;
	iofiles->tokens = NULL;
	iofiles->infile = NULL;
	iofiles->outfile = NULL;
	iofiles->tokens = (char **) malloc (sizeof(char *) * 20);
	
	while (tab[i])
	{
		if (!ft_strcmp(tab[i] , "<") || !ft_strcmp(tab[i], "<<"))
		{
			iofiles->infile = malloc (sizeof(char *) * 3);
			iofiles->infile[0] = ft_strdup(tab[i]);
			iofiles->infile[1] = ft_strdup(tab[i + 1]);
			iofiles->infile[2] = NULL;
			flag = 2;
		}	
		else if (!ft_strcmp(tab[i], ">") || !ft_strcmp(tab[i], ">>"))
		{
			iofiles->outfile = malloc(sizeof(char *) * 3);
			iofiles->outfile[0] = ft_strdup(tab[i]);
			iofiles->outfile[1] = ft_strdup(tab[i + 1]);
			iofiles->outfile[2] = NULL;
			flag = 2;
		}
		else if (flag == 0)
		{	
			fill_tokens(iofiles, tab, &i, &j);
			expand_var_env(wrp, iofiles, tab, i);
		}	
		
		flag = (flag > 0 ? flag - 1 : 0);
		i++;
	}
	iofiles->tokens[j] = NULL;
}

void		fill_tokens(t_iofiles *iofiles, char **tab, int *i, int *j)
{
	iofiles->tokens[*j] = ft_strdup(tab[*i]);
//	printf ("token[%d] : %s\n", *j, iofiles->tokens[*j]);
	*j += 1;	
}

void		expand_var_env(t_wrapper *wrp, t_iofiles *iofiles, char **tab, int index)
{
	int flag;
	char *dsign;
	int		start;

	flag = 0;
	if (is_squote(tab[index][0]))
		flag = 1;
	if (ft_strchr(tab[index], '$'))
	{
		tab_trimmer(tab);
		dsign = ft_strchr(tab[index], '$');
		start = dsign - tab[index];
		if (flag == 0)
			ft_env_var(wrp, iofiles, tab, index, start);
	}
}