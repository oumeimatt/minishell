/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 16:57:58 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/14 12:15:22 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    exec_exit(char **str)
{
	int	i;

	i = 0;
	if (str[1])
	{
		if (str[2] != NULL)
		{
			ft_putendl_fd("exit", 1);
			ft_putendl_fd("petitshell: exit: too many arguments", 2);
			g_i = 1;
			return ;
		}
		while (str[1][i] != '\0')
		{
			if (str[1][0] == '-' || str[1][0] == '+')
				i++;
			if (str[1][i] < 48 || str[1][i] > 57 || ft_strlen(str[1]) > 19)
			{
				ft_putendl_fd("exit", 1);
				ft_putstr_fd("petitshell: exit: ", 2);
				ft_putstr_fd(str[1], 2);
				ft_putendl_fd(": numeric argument required", 2);
				exit (255);
			}
			else
			{
				ft_putendl_fd("exit", 1);
				exit(ft_atoi(str[1]));
			}	
		}
	}
	else
	{
		ft_putendl_fd("exit", 1);
		exit (0);
	}
}	
