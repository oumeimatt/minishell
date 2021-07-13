/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 17:16:10 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/13 18:13:12 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void			signal_handler(int signum)
{    
    if (signum == SIGINT)
    {
        rl_newline(0, 0);
        rl_on_new_line();
        rl_redisplay();
    }
    if (signum == SIGQUIT)
        printf ("\n");
  //  return ;
}