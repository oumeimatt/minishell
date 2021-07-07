/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:34:31 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/07 19:14:01 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_cmd			cmd_create(char **tokens, char **line)
{
	t_cmd cmd;
	
	cmd.in = 0;
	cmd.out = 0;
	if (tokens)
	{
		cmd.tokens = (char **)malloc(sizeof(char *) * (tab_len(tokens) + 1));
		cmd.tokens = tokens;
		cmd.tokens[tab_len(tokens)] = NULL;
	}
	if (line)
		cmd.line = line;
	return (cmd);
}

void			cmd_destroy(t_cmd *cmd)
{
	destroy_tab(cmd->tokens);
}