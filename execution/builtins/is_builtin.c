/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 11:29:37 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/06 16:59:23 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
int    is_builtin(char **str, t_env *env) // str == tokens->cmd[0]
{
	if (strcmp(str[0], "echo") == 0)
		exec_echo(str);
	else if (strcmp(str[0], "cd") == 0)
		exec_cd(str, env);
	else if (strcmp(str[0], "pwd") == 0)
		exec_pwd();
	else if (strcmp(str[0], "export") == 0)
		exec_export(str, env);
	else if (strcmp(str[0], "unset") == 0)
		exec_unset(str, env);
	else if (strcmp(str[0], "env") == 0)	
		exec_env(env);
	else if (strcmp(str[0], "exit") == 0)
		exec_exit();
	else
		return (1);
	return (0);
}
