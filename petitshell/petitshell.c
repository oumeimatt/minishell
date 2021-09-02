/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   petitshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:43:45 by ztaouil           #+#    #+#             */
/*   Updated: 2021/09/02 19:38:02 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "petitshell.h"

int	main(int argc, char **argv, char **envp)
{
	t_wrapper	wrp;

	if (argc == 1 && argv[0])
	{
		parse_env(&(wrp.env), envp);
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		execution_loop(&wrp);
	}
	return (EXIT_SUCCESS);
}

void	execution_loop(t_wrapper *wrp)
{
	while (420)
	{
		if (parser(wrp))
		{
			// debug_pipeline(wrp->pipeline);
			execute(wrp);
			destroy_lcommand(wrp->pipeline);
		}
	}
}
