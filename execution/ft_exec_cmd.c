/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:09:56 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/09 17:19:39 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    exec_cmd(char **cmd)
{
	char	**wrng_cmd;

	if (execve(cmd[0], cmd, NULL) == -1)
	{
		wrng_cmd = ft_split_2(cmd[0], ' ');
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(wrng_cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
}

void	unset_path_cmd(t_wrapper *wrp)
{
	if (is_builtin(wrp->pipeline->cmd.tokens) == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(wrp->pipeline->cmd.tokens[0], 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	else
		exec_builtin(wrp->pipeline->cmd.tokens, wrp->env, 0);
}

void	ft_only_cmd(t_wrapper *wrp)
{
	char	*path;
	char	**split_path;
	pid_t	pid;

	path = get_path(wrp->env);
	if (path != NULL)
	{
		split_path = ft_split_2(path, ':');
		if (is_builtin(wrp->pipeline->cmd.tokens) == 1)
		{
			wrp->pipeline->cmd.tokens[0] = 
				absolute_path(wrp->pipeline->cmd.tokens[0], split_path);
			pid = fork();
			if (pid < 0)
				exit(1);
			if (pid == 0)
				exec_cmd(wrp->pipeline->cmd.tokens);
		}
		else
			exec_builtin(wrp->pipeline->cmd.tokens, wrp->env, 0);
		free(path);
	}
	else
		unset_path_cmd(wrp);
}
