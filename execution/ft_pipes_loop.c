/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 18:34:21 by oel-yous          #+#    #+#             */
/*   Updated: 2021/08/29 15:16:51 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_pipe_cmd_only(t_wrapper *wrp)
{
	g_vars.pid = fork();
	if (g_vars.pid < 0)
		exit(1);
	if (g_vars.pid == 0)
	{
		if (((t_command *)wrp->pipeline->data)->out != 1)
		{
			dup2(((t_command *)wrp->pipeline->data)->out, 1);
			if (wrp->pipeline->next)
				close(((t_command *)wrp->pipeline->next->data)->in);
		}
		if (((t_command *)wrp->pipeline->data)->in != 0)
			dup2(((t_command *)wrp->pipeline->data)->in, 0);
		if (is_builtin(((t_command *)wrp->pipeline->data)->tokens) == 1)
		{
			ft_only_cmd(wrp, 1);
			exec_cmd(((t_command *)wrp->pipeline->data)->tokens, wrp);
		}
		else
			exec_builtin(((t_command *)wrp->pipeline->data)->tokens, wrp->env, 1);
	}
	if (((t_command *)wrp->pipeline->data)->out != 1)
		close(((t_command *)wrp->pipeline->data)->out);		
	if (((t_command *)wrp->pipeline->data)->in != 0)
		close(((t_command *)wrp->pipeline->data)->in);
}

void	ft_pipe_cmd_redir(t_wrapper *wrp)
{
	g_vars.pid = fork();
	if (g_vars.pid < 0)
		exit(1);
	if (g_vars.pid == 0)
	{
		if (((t_command *)wrp->pipeline->data)->out != 1)
		{
			dup2(((t_command *)wrp->pipeline->data)->out, 1);
			close(((t_command *)wrp->pipeline->next->data)->in);
		}
		if (((t_command *)wrp->pipeline->data)->in != 0)
			dup2(((t_command *)wrp->pipeline->data)->in, 0);
		ft_exec_pipe_redir(wrp);
	}
	if (((t_command *)wrp->pipeline->data)->out != 1)
		close(((t_command *)wrp->pipeline->data)->out);
	if (((t_command *)wrp->pipeline->data)->in != 0)
		close(((t_command *)wrp->pipeline->data)->in);
}

void	ft_exec_pipe_redir(t_wrapper *wrp)
{
	char		*path;
	char		**split_path;

	path = get_path(wrp->env);
	split_path = ft_split_2(path, ':');
	((t_command *)(wrp->pipeline->data))->redir = ft_hook(((t_command *)(wrp->pipeline->data))->redir);
	if (path)
	{
		if (is_builtin(((t_command *)(wrp->pipeline->data))->tokens) == 1)
		{
			ft_is_redirection(((t_command *)(wrp->pipeline->data))->redir);
			((t_command *)(wrp->pipeline->data))->tokens[0] = 
				absolute_path(((t_command *)(wrp->pipeline->data))->tokens[0], split_path);
			ft_putendl_fd(((t_command *)(wrp->pipeline->data))->tokens[0], 2);
			exec_cmd(((t_command *)(wrp->pipeline->data))->tokens, wrp);
		}
		else
		{
			ft_is_redirection(((t_command *)(wrp->pipeline->data))->redir);
			exec_builtin(((t_command *)(wrp->pipeline->data))->tokens, wrp->env, 1);
		}
	}
	else
		ft_exec_pipe_redir_2(wrp);
}

void	ft_exec_pipe_redir_2(t_wrapper *wrp)
{
	ft_is_redirection(((t_command *)(wrp->pipeline->data))->redir);
	if (is_builtin(((t_command *)(wrp->pipeline->data))->tokens) == 1)
	{
		if (execve(((t_command *)(wrp->pipeline->data))->tokens[0], ((t_command *)(wrp->pipeline->data))->tokens, NULL) == -1)
		{
			ft_putstr_fd("petitshell: ", 2);
			ft_putstr_fd(((t_command *)(wrp->pipeline->data))->tokens[0], 2);
			ft_putendl_fd(": No such file or directory", 2);
			exit(127);
		}
	}
	else
		exec_builtin(((t_command *)(wrp->pipeline->data))->tokens, wrp->env, 1);
	
}

void	ft_pipe(t_wrapper *wrp)
{
	int		pipes[2];

	if (((t_command *)(wrp->pipeline->data))->out == 666)
	{
		pipe(pipes);
		((t_command *)(wrp->pipeline->data))->out = pipes[1];
		((t_command *)(wrp->pipeline->next->data))->in = pipes[0];
	}
}

void	ft_pipes_loop(t_wrapper *wrp)
{
	int		stats;

	stats = 0;
	while (wrp->pipeline)
	{
		ft_pipe(wrp);
		if (!(((t_command *)(wrp->pipeline->data))->redir))
			ft_pipe_cmd_only(wrp);
		else
			ft_pipe_cmd_redir(wrp);
		if (wrp->pipeline->next == NULL)
			break;
		wrp->pipeline = wrp->pipeline->next;
	}
	while (waitpid(-1, &stats, 0)> 0)
	{
		if (WIFEXITED(stats))
			g_vars.i = WEXITSTATUS(stats);
	}
}