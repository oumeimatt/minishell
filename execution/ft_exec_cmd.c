/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:09:56 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/16 17:57:17 by oel-yous         ###   ########.fr       */
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

void	unset_path_cmd(t_wrapper *wrp, int i)
{
	int		stats;

	if (is_builtin(wrp->pipeline->cmd.tokens) == 1)
	{
		if (i == 0)
		{
			wrp->pipeline->cmd.pid = fork();
			if (wrp->pipeline->cmd.pid < 0)
				exit(1);
			if (wrp->pipeline->cmd.pid == 0)
			{
				if (execve(wrp->pipeline->cmd.tokens[0], wrp->pipeline->cmd.tokens, NULL) == -1)
				{
					ft_putstr_fd("minishell: ", 2);
					ft_putstr_fd(wrp->pipeline->cmd.tokens[0], 2);
					ft_putendl_fd(": No such file or directory", 2);
					exit(127);
				}
			}
			waitpid(wrp->pipeline->cmd.pid, &stats, 0);
			if (WIFEXITED(stats))
				g_i = WEXITSTATUS(stats);
		}
	}
	else
	{
		if (i == 0)
			exec_builtin(wrp->pipeline->cmd.tokens, wrp->env, 0);
		else
			exec_builtin(wrp->pipeline->cmd.tokens, wrp->env, 1);
	}
}

void	ft_only_cmd(t_wrapper *wrp, int i)
{
	char	*path = NULL;
	char	**split_path;
	int		stats;

	if (wrp->pipeline->cmd.tokens[0][0] != '.')
		path = get_path(wrp->env);
	if (path != NULL)
	{
		split_path = ft_split_2(path, ':');
		if (is_builtin(wrp->pipeline->cmd.tokens) == 1)
		{
			wrp->pipeline->cmd.tokens[0] =
				absolute_path(wrp->pipeline->cmd.tokens[0], split_path);
			if (i == 0)
			{
				wrp->pipeline->cmd.pid = fork();
				if (wrp->pipeline->cmd.pid < 0)
					exit(1);
				if (wrp->pipeline->cmd.pid == 0)
					exec_cmd(wrp->pipeline->cmd.tokens);
				waitpid(wrp->pipeline->cmd.pid, &stats, 0);
				if (WIFEXITED(stats))
					g_i = WEXITSTATUS(stats);
			}
		}
		else
			exec_builtin(wrp->pipeline->cmd.tokens, wrp->env, 0);
	}
	else
	{
		if (i == 0)
			unset_path_cmd(wrp, 0);
		else
			unset_path_cmd(wrp, 1);
	}
}
