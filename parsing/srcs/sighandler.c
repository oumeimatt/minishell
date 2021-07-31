/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 17:16:10 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/16 15:30:32 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void			child_process(int signum)
{
	if (!kill(g_variables.pid, signum))
	{
		if (signum == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 1);
			g_variables.i = 131;
		}
		else if (signum == SIGINT)
		{
			ft_putchar_fd('\n', 1);
			g_variables.i = 130;
		}
	}
	else if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		ft_putchar_fd('\r', 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void			signal_handler(int signum)
{    
	if ((signum == SIGINT || signum == SIGQUIT) && g_variables.pid != 0)
		child_process(signum);
	else
	{	
		if (signum == SIGINT)
		{
			ft_putchar_fd('\n', 2);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay(); 
		}
		else if (signum == SIGQUIT)
		{
			ft_putchar_fd('\r', 2);
			rl_on_new_line();
			rl_redisplay();
		}
	}
	return ;
}
