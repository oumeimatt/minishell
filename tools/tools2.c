/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 17:55:16 by ztaouil           #+#    #+#             */
/*   Updated: 2021/09/04 18:58:58 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

int	check_line_syntax(char *string)
{
	int	s_count;
	int	len;
	int	d_quote;

	d_quote = 2;
	s_count = 0;
	len = ft_strlen(string);
	if (!ft_strcmp(string, "\n") || spaces(string))
		return (0);
	if (!export_check_quotes(string))
		return (-10);
	if (!ft_strncmp(string, "| |", 3))
		return (-2);
	else if (!ft_strncmp(string, "|", 1))
		return (-1);
	else if ((!ft_strncmp(string, "\"", 1) && len < 2)
		|| (!ft_strncmp(string, "\'", 1) && len < 2)
		|| (string[len - 1] == '|' && string[len] == '\0')
		|| *string == 0)
		return (-10);
	return (check_line_syntax2(string));
}

static int	check_line_syntax5(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if ((string[i] == '<' && string[i + 1] == '\0')
			|| (string[i] == '<' && string[i + 1] == '<'
				&& string[i + 2] == '\0'))
			return (-3);
		else if ((string[i] == '<' && string[i + 1] == '<'
				&& string[i + 2] == '<' && string[i + 3] == '\0'))
			return (-3);
		else if ((string[i] == '>' && string[i + 1] == '\0')
			|| (string[i] == '>' && string[i + 1] == '>'
				&& string[i + 2] == '\0'))
			return (-3);
		i++;
	}
	return (1);
}

static int	check_line_syntax4(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == '<' && string[i + 1] == '>')
			return (-3);
		else if ((string[i] == '>' && string[i + 1] == '>'
				&& string[i + 2] == '>' && string[i + 3] == '\0'))
			return (-4);
		i++;
	}
	return (check_line_syntax5(string));
}

static int	check_line_syntax3(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if ((string[i] == '>' && string[i + 1] == '>'
				&& string[i + 2] == '>' && string[i + 3] == '>'
				&& string[i + 4] == '\0'))
			return (-5);
		else if (string[i] == '>' && string[i + 1] == '<')
			return (-6);
		i++;
	}
	return (check_line_syntax4(string));
}

int	check_line_syntax2(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if ((string[i] == '<' && string[i + 1] == '<'
				&& string[i + 2] == '<' && string[i + 3] == '<'
				&& string[i + 4] == '\0'))
			return (-6);
		else if ((string[i] == '<' && string[i + 1] == '<'
				&& string[i + 2] == '<' && string[i + 3] == '<'
				&& string[i + 4] == '<' && string[i + 5] == '\0'))
			return (-7);
		i++;
	}
	return (check_line_syntax3(string));
}
