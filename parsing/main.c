/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 17:08:13 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/13 18:11:41 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int         main(int argc, char **argv, char **envp)
{
	t_wrapper *wrp;
	(void)argc;
	(void)argv;
	wrp = contruct_wrapper();
		
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	parser(wrp, envp);

	return (EXIT_SUCCESS);
}