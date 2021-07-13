/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 17:16:10 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/13 17:30:04 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void			sigint_handler(int signum)
{
	if (signum == SIGINT)
        printf ("\nget lost! %d\n", signum);
    else if (signum == SIGQUIT)
        printf ("\nipip %d\n!", signum);
  //  return ;
}