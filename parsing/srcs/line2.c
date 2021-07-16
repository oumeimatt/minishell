/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 13:49:13 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/16 17:59:39 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int			check_line_syntax(char *string)
{
	int	s_count;
	int len;
	int d_quote;
	
	d_quote = 2;
	s_count = 0;
	len = ft_strlen(string);
	if (!ft_strcmp(string, "\n"))
		return (0);
	if (!ft_strncmp(string, "| |", 3))
		return (-2);
	else if (!ft_strncmp(string, "|", 1))
		return (-1);
	else if ((!ft_strncmp(string, "\"", 1) && len < 2) || (!ft_strncmp(string, "\'", 1) && len < 2) || (string[len - 1] == '|' && string[len] == '\0') || *string == 0)
		return (0);
	while (string[s_count])
	{
		if (is_dquote(string[s_count]))
			d_quote++;
		s_count++;
	}
	if (!(d_quote % 2 == 0))
		return (0);
	return (check_line_syntax2(string));
}

int			check_line_syntax2(char *string)
{
	int 	i;

	i = 0;
	while (string[i])
	{
		if ((string[i] == '<' && string[i + 1] == '\0') || (string[i] == '<' && string[i + 1] == '<' && string[i + 2] == '\0'))
			return (-3);
		else if ((string[i] == '<' && string[i + 1] == '<' && string[i + 2] == '<' && string[i + 3] == '\0'))
			return (-3);
		else if ((string[i] == '>' && string[i + 1] == '\0') || (string[i] == '>' && string[i + 1] == '>' && string[i + 2] == '\0'))
			return (-3);
		else if (string[i] == '<' && string[i + 1] == '>')
			return (-3);
		else if ((string[i] == '>' && string[i + 1] == '>' && string[i + 2] == '>' && string[i + 3] == '\0'))
			return (-4);
		else if ((string[i] == '>' && string[i + 1] == '>' && string[i + 2] == '>' && string[i + 3] == '>' && string[i + 4] == '\0'))
			return (-5);
		else if (string[i] == '>' && string[i + 1] == '<')
			return (-6);
		i++;
	}
	return (check_line_syntax3(string));
}

int			check_line_syntax3(char *string)
{
	int i;

	i = 0;
	while (string[i])
	{
		if ((string[i] == '<' && string[i + 1] == '<' && string[i + 2] == '<' && string[i + 3] == '<' && string[i + 4] == '\0'))
			return (-6);
		else if ((string[i] == '<' && string[i + 1] == '<' && string[i + 2] == '<' && string[i + 3] == '<' && string[i + 4] == '<' && string[i + 5] == '\0'))
			return (-7);
		i++;
	}
	return (1);	
}

char		*expand_exit_code(t_wrapper *wrp, char *string)
{
	int i;
	int j;
	char *str;

	(void)wrp;
	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * ft_strlen(string) * 2);
	if (!str)
		return (NULL);
	while (string[i] != '\0')
	{
		if (is_dollar(string[i]) && string[i + 1] == '?')
		{
			str = ft_strjoin(str, ft_itoa(g_i));
			j += ft_strlen(ft_itoa(g_i));
			i += 2;
		}
		if (string[i] != '\0')
			str[j++] = string[i++];
	}
	str[j] = '\0';
	return (str);	
}