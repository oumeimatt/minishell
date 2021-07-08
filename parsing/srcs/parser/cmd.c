/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:34:31 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/08 18:22:42 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_cmd			cmd_create(char **tokens)
{
	t_cmd cmd;
	

	cmd.tokens = (char **)malloc(sizeof(char *) * (tab_len(tokens) + 1));
	if (tokens)
	{
		cmd.tokens = tokens;
		cmd.tokens[tab_len(tokens)] = NULL;
	}
	return (cmd);
}

void			cmd_destroy(t_cmd *cmd)
{
	destroy_tab(cmd->tokens);
}