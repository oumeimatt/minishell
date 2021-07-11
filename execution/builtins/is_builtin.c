/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 11:29:37 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/11 20:39:52 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		is_builtin(char	**str)
{
	if (!str[0])
		return (0);
	if (!ft_strcmp(str[0], "echo") || !ft_strcmp(str[0], "cd") ||
		 !ft_strcmp(str[0], "pwd") || !ft_strcmp(str[0], "export") ||
		!ft_strcmp(str[0], "env") || !ft_strcmp(str[0], "exit") || 
		!ft_strcmp(str[0], "unset"))
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
