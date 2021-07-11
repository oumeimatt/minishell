/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 17:34:09 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/10 14:19:40 by ztaouil          ###   ########.fr       */
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
	j = tab_len(tab);
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
	t_lstredir *tmp;

	j = 0;
	i = 0;
	flag = 0;

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
			expand_var_env(wrp, iofiles, tab, i);
		}	
		
		flag = (flag > 0 ? flag - 1 : 0);
		//printf ("tab[%d] : %s\n", i, tab[i]);
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