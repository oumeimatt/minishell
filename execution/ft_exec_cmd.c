/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:09:56 by oel-yous          #+#    #+#             */
/*   Updated: 2021/08/29 16:26:34 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void    exec_cmd(char **cmd, t_wrapper *wrp)
{
	char	**wrng_cmd;
	char	**arr;

	arr = list_to_arr(wrp->env);
	if (execve(cmd[0], cmd, arr) == -1 && (ft_strncmp(cmd[0], "./", 2) &&
		ft_strncmp(cmd[0], "../", 2)))
	{
		wrng_cmd = ft_split_2(cmd[0], ' ');
		ft_putstr_fd("petitshell: ", 2);
		ft_putstr_fd(wrng_cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	else
	{
		wrng_cmd = ft_split_2(cmd[0], ' ');
		ft_putstr_fd("petitshell: ", 2);
		ft_putstr_fd(wrng_cmd[0], 2);
		ft_putendl_fd(": permission denied", 2);
		exit(126);
	}
}

void	unset_path_cmd(t_wrapper *wrp, int i)
{
	int		stats;

	if (is_builtin(((t_command *)(wrp->pipeline->data))->tokens) == 1)
	{
		if (i == 0)
		{
			g_vars.pid = fork();
			if (g_vars.pid < 0)
				exit(1);
			if (g_vars.pid == 0)
			{
				if (execve(((t_command *)(wrp->pipeline->data))->tokens[0], ((t_command *)(wrp->pipeline->data))->tokens, NULL) == -1)
				{
					ft_putstr_fd("minishell: ", 2);
					ft_putstr_fd(((t_command *)(wrp->pipeline->data))->tokens[0], 2);
					ft_putendl_fd(": No such file or directory", 2);
					exit(127);
				}
			}
			waitpid(g_vars.pid, &stats, 0);
			if (WIFEXITED(stats))
				g_vars.i = WEXITSTATUS(stats);
		}
	}
	else
	{
		if (i == 0)
			exec_builtin(((t_command *)(wrp->pipeline->data))->tokens, wrp->env, 0);
		else
			exec_builtin(((t_command *)(wrp->pipeline->data))->tokens, wrp->env, 1);
	}
}

void	ft_only_cmd(t_wrapper *wrp, int i)
{
	char	*path = NULL;
	char	**split_path;
	int		stats;

	path = get_path(wrp->env);
	if (path != NULL)
	{
		split_path = ft_split_2(path, ':');
		if (is_builtin(((t_command *)(wrp->pipeline->data))->tokens) == 1)
		{
			((t_command *)(wrp->pipeline->data))->tokens[0] =
				absolute_path(((t_command *)(wrp->pipeline->data))->tokens[0], split_path);
			if (i == 0)
			{
				g_vars.pid = fork();
				if (g_vars.pid < 0)
					exit(1);
				if (g_vars.pid == 0)
					exec_cmd(((t_command *)(wrp->pipeline->data))->tokens, wrp);
				waitpid(g_vars.pid, &stats, 0);
				if (WIFEXITED(stats))
					g_vars.i = WEXITSTATUS(stats);
			}
		}
		else
			exec_builtin(((t_command *)(wrp->pipeline->data))->tokens, wrp->env, 0);
	}
	else
	{
		if (i == 0)
			unset_path_cmd(wrp, 0);
		else
			unset_path_cmd(wrp, 1);
	}
}
