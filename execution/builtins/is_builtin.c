/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 11:29:37 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/06 12:46:58 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing/inc/minishell.h"

void    is_builtin(char **str, t_env *env) // str == tokens->cmd[0]
{
	if (strcmp(str[0], "echo") == 0)
		exec_echo(str);
	if (strcmp(str[0], "cd") == 0)
		exec_cd(str, env);
	if (strcmp(str[0], "pwd") == 0)
		exec_pwd();
	if (strcmp(str[0], "export") == 0)
		exec_export(str, env);
	if (strcmp(str[0], "unset") == 0)
		exec_unset(str, env);
	if (strcmp(str[0], "env") == 0)	
		exec_env(env);
// 	if (strcmp(str[0], "exit") == 0)
// 		exec_exit();
}
