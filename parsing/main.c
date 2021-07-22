/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 17:08:13 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/15 20:07:47 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_wrapper	*wrp;

	(void)argc;
	(void)argv;
	wrp = contruct_wrapper();
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	parser(wrp, env);
	return (EXIT_SUCCESS);
}