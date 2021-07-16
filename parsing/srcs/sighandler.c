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

void			signal_handler(int signum)
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
		ft_putchar_fd(0, 2);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}
