/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:56:17 by ztaouil           #+#    #+#             */
/*   Updated: 2021/09/02 18:21:15 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

int	export_check_quotes(char *line)
{
	int		i;
	char	tmp;
	int		d_flag;
	int		s_flag;

	tmp = 0;
	i = 0;
	d_flag = 0;
	s_flag = 0;
	//printf ("export check quotes		%s		%d		%d\n", line);
	while (line[i++] != '\0')
	{
		if (is_dquote(line[i]) && !d_flag)
			d_flag = 1;
		else if (is_dquote(line[i]) && d_flag)
			d_flag = 0;
		if (is_squote(line[i]) && !s_flag)
			s_flag = 1;
		else if (is_squote(line[i]) && s_flag)
			s_flag = 0;
	}
	//printf ("export check quotes		%s		%d		%d\n", line);
	if (!s_flag && !d_flag)
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

static void	ext_exit_code(char *string, int *i, char *str, int *j)
{
	int		c_count;
	char	*tmp;

	c_count = 0;
	if (is_dollar(string[*i]) && string[*i + 1] == '?')
	{
		tmp = ft_itoa(g_vars.i);
		while (tmp[c_count] != '\0')
			str[(*j)++] = tmp[c_count++];
		free (tmp);
		*i += 2;
	}
}

char	*expand_exit_code(char *string)
{
	int		i;
	int		j;
	char	*str;
	int		c_count;

	i = 0;
	j = 0;
	c_count = 0;
	str = (char *)malloc(sizeof(char) * ft_strlen(string) * 5);
	if (!str)
		return (NULL);
	while (string[i] != '\0')
	{
		ext_exit_code(string, &i, str, &j);
		if (string[i] != '\0')
			str[j++] = string[i++];
	}
	str[j] = '\0';
	free (string);
	return (str);
}

int	dollar_valid(char c)
{
	if (c == '\'' || c == '"' || c == '\0')
		return (1);
	return (0);
}
