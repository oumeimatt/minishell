/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 19:24:23 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/13 16:42:52 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		get_len_env(char *string)
{
	int p_count;

	p_count = 0;
	while (string[p_count] != '\0' && ft_isalnum(string[p_count]))
		p_count++;
	return (p_count);
}

int  dollar_valid(char c)
{
	if (c == '\'' || c == '"' || c == '\0')
		return (1);
	return (0);
}

char *expand_env(t_wrapper *wrp, char *string)
{
	int p_count;
	int s_count;
	char *str;
	char *value;
	int c_count;
	int s_flag;
	int d_flag;

	s_flag = 0;
	d_flag = 0;
	p_count = 0;
	s_count = 0;
	str = (char *)malloc(sizeof(char) * ft_strlen(string) * 100);
	if (!str)
		return (NULL);
	while (string[p_count] != '\0')
	{
		if (is_dquote(string[p_count]) && !d_flag)
			d_flag = 0;
		else if (is_dquote(string[p_count] && d_flag))
			d_flag = 1;
		if (string[p_count] == '\'' && !s_flag && string[p_count - 1] != '\'')
			s_flag = 1;
		else if (string[p_count] == '\'' && s_flag)
			s_flag = 0;
		if (is_dollar(string[p_count]) && !dollar_valid(string[p_count + 1]) && !s_flag)
		{
			p_count++;
			value = print_value(wrp->env, ft_substr(string, p_count, get_len_env(&string[p_count])));
			p_count += get_len_env(&string[p_count]);
			c_count = 0;
			while (value && value[c_count] != '\0')
				str[s_count++] = value[c_count++];
		}
		if (string[p_count] != '$'|| (is_dollar(string[p_count]) && dollar_valid(string[p_count + 1])) || (is_dollar(string[p_count]) && s_flag))
			str[s_count++] = string[p_count++];
	}
	str[s_count] = '\0';
	return (str);
}