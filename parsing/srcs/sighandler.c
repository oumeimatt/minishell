/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 17:16:10 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/13 19:49:15 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void			signal_handler(int signum)
{    
	if (signum == SIGINT)
	{
		rl_on_new_line();
		//rl_replace_line();
		ft_putstr_fd("\n", 2);
		ft_putstr_fd(BHBLU "petitshell-1.0" reset BHWHT "$ " reset, 2);
		rl_redisplay(); 
	}
	else if (signum == SIGQUIT)
	{
		ft_putstr_fd("\n", 2);
		ft_putstr_fd(BHBLU "petitshell-1.0" reset BHWHT "$ " reset, 2);
	}
	return ;
}
