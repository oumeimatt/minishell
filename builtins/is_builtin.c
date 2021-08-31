/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 11:29:37 by oel-yous          #+#    #+#             */
/*   Updated: 2021/08/31 14:30:44 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		is_builtin(char	**str)
{
	if (!str[0])
		return (2);
	if (!ft_strcmp(str[0], "echo") || !ft_strcmp(str[0], "cd") ||
		 !ft_strcmp(str[0], "pwd") || !ft_strcmp(str[0], "export") ||
		!ft_strcmp(str[0], "env") || !ft_strcmp(str[0], "exit") || 
		!ft_strcmp(str[0], "unset"))
		return (0);
	return (1);
}

void    exec_builtin(char **str, t_list **env, int i) 
{
	if (!ft_strcmp(str[0], "echo"))
		exec_echo(str, i);
	else if (!ft_strcmp(str[0], "cd"))
		exec_cd(str, env, i);
	else if (!ft_strcmp(str[0], "pwd"))
		exec_pwd(env, i);
	else if (!ft_strcmp(str[0], "export"))
		exec_export(str, env, i);
	else if (!ft_strcmp(str[0], "unset"))
		exec_unset(str, env, i);
	else if (!ft_strcmp(str[0], "env"))	
		exec_env(env, i);
	else if (!ft_strcmp(str[0], "exit"))
		exec_exit(str);
}
