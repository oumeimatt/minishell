/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 17:34:09 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/10 17:31:48 by ztaouil          ###   ########.fr       */
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
			expand_var_env(wrp, iofiles, tab[i], i);
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

char 		**get_env_vars_keys(char *token)
{
	int	i;
	char **tab;
	int		j;
	
	tab = (char **)malloc(sizeof(char *) * 20);
	i = ft_strlen (token);
	j = 0;
	while (i >= 0)
	{
		if (is_dollar(token[i]))
		{
			tab[j++] = ft_substr(token, i + 1, ft_strlen(token) - i - 1);
			token = ft_substr(token, 0, i);
		}
		i--;
	}
	tab[j] = NULL;	
	return (tab);
}

void		expand_var_env(t_wrapper *wrp, t_iofiles *iofiles, char *token, int index)
{
	char **tab; 
	int len;
	int i;
	int j;
	char *tmp;
	
	tab = get_env_vars_keys(token);
	len = get_env_var_token_len(wrp, token);
	j = tab_len(tab) - 1;
	i = 0;
	if (j == -1)
		return ;
	iofiles->tokens[index] = malloc (sizeof(char) * len);
	while (token[i] != '\0' && !is_dollar(token[i]))
	{
		iofiles->tokens[index][i] = token[i];
		i++;
	}
	while (j >= 0)
	{	
		tmp = print_value(wrp->env, tab[j]);
		iofiles->tokens[index] = ft_strjoin(iofiles->tokens[index], tmp);
		j--;
	}
}

int			get_env_var_token_len(t_wrapper *wrp, char *token)
{
	char **tab; 
	int i = 0;
	int len = 0;
	int j;
	char *tmp;
	
	tab = get_env_vars_keys(token);
	j = tab_len(tab) - 1;
	if (j > -1)
	{	
		while (token[i])
		{
			if (!is_dollar(token[i]))
				len++;
			else
				while (j >= 0)
				{
					tmp = print_value(wrp->env, tab[j]);
					if (tmp)
						len += ft_strlen(tmp);
					j--;
				}
			i++;
		}
	}
	return (len);
}