/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 13:51:29 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/06 13:14:02 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		echo_valid_option(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '-')
	{
		while (str[i] != '\0')
		{
			if (str[i] != 'n')
				return (FALSE);
			i++;
		}
		return(TRUE);
	}
	return(FALSE);
}
void	echo_option_exist(char **str)
{
	int		i;

	if (str[2] == NULL)
		return;
	i = 2;
	while (echo_valid_option(str[i]) == TRUE)
	{
		i++;
		if (str[i] == NULL)
			return;
	}
	while (str[i] != NULL)
	{
		
		printf("%s", str[i]);
		i++;
		if (str[i] != NULL)
			printf(" ");
	}
}

void   exec_echo(char **str)
{
	int	j;

	if (str[1] == NULL)
		printf("\n");
	else
	{
		if (echo_valid_option(str[1]) == TRUE)
			echo_option_exist(str);
		else
		{
			j = 1;
			while (str[j] != NULL)
			{
				printf("%s ", str[j]);
				j++;
			}
			printf("\n");
		}
	}   
}        
