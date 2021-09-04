/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 16:57:58 by oel-yous          #+#    #+#             */
/*   Updated: 2021/09/04 15:18:43 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	exit_helper(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[0] == '-' || str[0] == '+')
			i++;
		if (str[i] < 48 || str[i] > 57
			|| ft_strcmp(str, ft_itoa(ft_atoi(str))))
		{
			ft_putendl_fd("exit", 1);
			ft_putstr_fd("petitshell: exit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putendl_fd(": numeric argument required", 2);
			exit (255);
		}
		else
		{
			ft_putendl_fd("exit", 1);
			exit(ft_atoi(str));
		}	
	}	
}

void	exec_exit(char **str)
{
	if (str[1])
	{
		if (str[2] != NULL)
		{
			ft_putendl_fd("exit", 1);
			ft_putendl_fd("petitshell: exit: too many arguments", 2);
			g_vars.i = 1;
			return ;
		}
		if (!ft_strcmp(str[1], "-9223372036854775808"))
		{
			ft_putendl_fd("exit", 1);
			exit(0);
		}
		exit_helper(str[1]);
	}
	else
	{
		ft_putendl_fd("exit", 1);
		exit (0);
	}
}
