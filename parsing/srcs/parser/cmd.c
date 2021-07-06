/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:34:31 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/06 18:39:46 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_cmd			cmd_create(char **tokens, char **in_files, char **out_files)
{
	t_cmd cmd;
	if (tokens)
	{
		cmd.tokens = (char **)malloc(sizeof(char *) * (tab_len(tokens) + 1));
		cmd.tokens = tokens;
		cmd.tokens[tab_len(tokens)] = NULL;
	}
	if (in_files)
	{
		cmd.input_files = (char **)malloc(sizeof(char *) * (tab_len(in_files) + 1));
		cmd.input_files = in_files;
		cmd.input_files[tab_len(in_files)] = NULL;
	}
	if (out_files)
	{
		cmd.output_files = (char **)malloc(sizeof(char *) * (tab_len(out_files) + 1));
		cmd.output_files = out_files;
		cmd.output_files[tab_len(out_files)] = NULL;
	}
	return (cmd);
}

void			cmd_destroy(t_cmd *cmd)
{
	destroy_tab(cmd->tokens);
}