/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 11:29:37 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/09 17:44:01 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		is_builtin(char	**str)
{
	if (!strcmp(str[0], "echo") || !strcmp(str[0], "cd") ||
		 !strcmp(str[0], "pwd") || !strcmp(str[0], "export") ||
		!strcmp(str[0], "env") || !strcmp(str[0], "exit") || 
		!strcmp(str[0], "unset"))
		return (0);
	return (1);
}

void    exec_builtin(char **str, t_env *env, int i) 
{
	if (strcmp(str[0], "echo") == 0)
		exec_echo(str, i);
	else if (strcmp(str[0], "cd") == 0)
		exec_cd(str, env, i);
	else if (strcmp(str[0], "pwd") == 0)
		exec_pwd( i);
	else if (strcmp(str[0], "export") == 0)
		exec_export(str, env, i);
	else if (strcmp(str[0], "unset") == 0)
		exec_unset(str, env, i);
	else if (strcmp(str[0], "env") == 0)	
		exec_env(env, i);
	else if (strcmp(str[0], "exit") == 0)
		exec_exit();
}
