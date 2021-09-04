/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 17:11:27 by ztaouil           #+#    #+#             */
/*   Updated: 2021/09/04 15:53:23 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

int	dollar_valid(char c)
{
	if (c == '\'' || c == '"' || c == '\0')
		return (1);
	return (0);
}

int	get_len_env(char *string)
{
	int	p_count;

	p_count = 0;
	while (string[p_count] != '\0' && ft_isalnum(string[p_count]))
		p_count++;
	return (p_count);
}

int	norm_help1(t_reform env, const char *string)
{
	if ((is_dquote(string[(env.p_count)])
			|| is_squote(string[(env.p_count)])) && !env.quote)
		return (1);
	return (0);
}

int	norm_help2(t_reform env, const char *string)
{
	if ((is_dquote(string[(env.p_count)])
			|| is_squote(string[(env.p_count)])) && env.quote)
		return (1);
	return (0);
}

int	norm_help3(t_reform env, const char *string)
{
	if (is_redir(string[(env.p_count) + 1])
		&& !is_redir(string[(env.p_count)])
		&& string[(env.p_count)] != ' ' && env.quote == 0)
		return (1);
	return (0);
}
