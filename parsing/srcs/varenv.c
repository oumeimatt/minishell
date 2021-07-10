/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 19:24:23 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/10 21:53:08 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

int		get_env_len(char *string)
{
	int p_count;

	p_count = 0;
	while (string[p_count] != '\0' && ft_isalnum(string[p_count]))
		p_count++;
	return (p_count);
}

char *expand_env(t_wrapper *wrp, char *string)
{
	int p_count;
	int s_count;
	char *str;
	char *value;
	int c_count;
	int s_flag;


	s_flag = 0;
	p_count = 0;
	s_count = 0;
	str = (char *)malloc(sizeof(char) * ft_strlen(string) * 100);
	if (!str)
		return (NULL);
	while (string[p_count] != '\0')
	{
		if (string[p_count] == '\'' && !s_flag)
			s_flag = 1;
		else if (string[p_count] == '\'' && s_flag)
			s_flag = 0;
		if (is_dollar(string[p_count]) && !s_flag)
		{
			p_count++;
			value = print_value(wrp->env, ft_substr(string, p_count, get_env_len(&string[p_count])));
			p_count += get_env_len(&string[p_count]);
			c_count = 0;
			while (value && value[c_count] != '\0')
				str[s_count++] = value[c_count++];
		}
		if (!is_dollar(string[p_count]) || s_flag)
			str[s_count++] = string[p_count++];
	}
	str[s_count] = '\0';
	return (str);
}