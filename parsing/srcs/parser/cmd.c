/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:34:31 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/05 18:02:46 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_cmd			cmd_create(char **tokens, char **in_files, char *out_files)
{
	t_cmd cmd;

	cmd.tokens = (char **)malloc(sizeof(char *) * GetTabSize(tokens));
	cmd.tokens = tokens;
	cmd.input_files = in_files;
	cmd.output_files = out_files;
	return (cmd);
}

void			cmd_destroy(t_cmd *cmd)
{
	int len;

	len = GetTabSize(cmd->tokens);
	destroy_tab(cmd->tokens);
}