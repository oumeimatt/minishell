/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 18:34:21 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/16 16:49:38 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    ft_pipe_cmd_only(t_wrapper *wrp)
{
	wrp->pipeline->cmd.pid = fork();
	if (wrp->pipeline->cmd.pid < 0)
		exit(1);
	if (wrp->pipeline->cmd.pid == 0)
	{
		if (wrp->pipeline->out != 1)
		{
			dup2(wrp->pipeline->out, 1);
			close(wrp->pipeline->next->in);
		}
		if (wrp->pipeline->in != 0)
		{
			dup2(wrp->pipeline->in, 0);
		}
		if (is_builtin(wrp->pipeline->cmd.tokens) == 1)
		{
			ft_only_cmd(wrp, 1);
			exec_cmd(wrp->pipeline->cmd.tokens, wrp);
		}
		else
			exec_builtin(wrp->pipeline->cmd.tokens, wrp->env, 1);
	}
	if (wrp->pipeline->out != 1)
		close(wrp->pipeline->out);
	if (wrp->pipeline->in != 0)
		close(wrp->pipeline->in);
}

void	ft_pipe_cmd_redir(t_wrapper *wrp)
{
	wrp->pipeline->cmd.pid = fork();
	if (wrp->pipeline->cmd.pid < 0)
		exit(1);
	if (wrp->pipeline->cmd.pid == 0)
	{
		if (wrp->pipeline->out != 1)
		{
			dup2(wrp->pipeline->out, 1);
			close(wrp->pipeline->next->in);
		}
		if (wrp->pipeline->in != 0)
			dup2(wrp->pipeline->in, 0);
		ft_exec_pipe_redir(wrp);
	}
	if (wrp->pipeline->out != 1)
		close(wrp->pipeline->out);
	if (wrp->pipeline->in != 0)
		close(wrp->pipeline->in);
}

void	ft_exec_pipe_redir(t_wrapper *wrp)
{
	char		*path;
	char		**split_path;

	path = get_path(wrp->env);
	split_path = ft_split_2(path, ':');
	wrp->pipeline->redir = ft_hook(wrp->pipeline->redir);
	if (path)
	{
		if (is_builtin(wrp->pipeline->cmd.tokens) == 1)
		{
			ft_is_redirection(wrp->pipeline->redir);
			wrp->pipeline->cmd.tokens[0] = 
				absolute_path(wrp->pipeline->cmd.tokens[0], split_path);
			ft_putendl_fd(wrp->pipeline->cmd.tokens[0], 2);
			exec_cmd(wrp->pipeline->cmd.tokens, wrp);
		}
		else
		{
			ft_is_redirection(wrp->pipeline->redir);
			exec_builtin(wrp->pipeline->cmd.tokens, wrp->env, 1);
		}
	}
	else
		ft_exec_pipe_redir_2(wrp);
}

void	ft_exec_pipe_redir_2(t_wrapper *wrp)
{
	ft_is_redirection(wrp->pipeline->redir);
	if (is_builtin(wrp->pipeline->cmd.tokens) == 1)
	{
		if (execve(wrp->pipeline->cmd.tokens[0], wrp->pipeline->cmd.tokens, NULL) == -1)
		{
			ft_putstr_fd("petitshell: ", 2);
			ft_putstr_fd(wrp->pipeline->cmd.tokens[0], 2);
			ft_putendl_fd(": No such file or directory", 2);
			exit(127);
		}
	}
	else
		exec_builtin(wrp->pipeline->cmd.tokens, wrp->env, 1);
	
}

void	ft_pipe(t_wrapper *wrp)
{
	int		pipes[2];

	if (wrp->pipeline->out == 666)
	{
		pipe(pipes);
		wrp->pipeline->out = pipes[1];
		wrp->pipeline->next->in = pipes[0];
	}
}

void	ft_pipes_loop(t_wrapper *wrp)
{
	int		stats;

	stats = 0;
	while (wrp->pipeline)
	{
		ft_pipe(wrp);
		if (!wrp->pipeline->redir)
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
			g_i = WEXITSTATUS(stats);
	}
}