/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:56:21 by ztaouil           #+#    #+#             */
/*   Updated: 2021/09/02 18:37:02 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

char	*ext_tab_trimmer(char *string)
{
	int		c_count;
	int		p_count;
	char	*str;

	str = malloc(sizeof(char) * ft_strlen(string) + 2);
	if (!str)
		return (NULL);
	p_count = 0;
	c_count = 0;
	while (string[c_count] != '\0')
	{
		if (is_dquote(string[c_count]) || is_squote(string[c_count]))
			c_count++;
		if (string[c_count])
			str[p_count++] = string[c_count++];
	}
	str[p_count] = '\0';
	free (string);
	return (str);
}

void	tab_trimmer(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		tab[i] = ft_strtrim(tab[i], "\"\'");
		tab[i] = ext_tab_trimmer(tab[i]);
		i++;
	}
}

void	debug_tab(char **tab)
{
	int	i;

	for (i = 0; tab[i + 1]; i++)
		printf (" [%s] -", tab[i]);
	printf (" [%s]", tab[i]);
}

int	spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
