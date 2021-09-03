/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 18:34:21 by oel-yous          #+#    #+#             */
/*   Updated: 2021/09/03 13:19:49 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_pipe_cmd_only(t_list *pipeline, t_list **env)
{
	g_vars.pid = fork();
	if (g_vars.pid < 0)
		exit(1);
	if (g_vars.pid == 0)
	{
		if (((t_command *)pipeline->data)->out != 1)
		{
			dup2(((t_command *)pipeline->data)->out, 1);
			if (pipeline->next)
				close(((t_command *)pipeline->next->data)->in);
		}
		if (((t_command *)pipeline->data)->in != 0)
			dup2(((t_command *)pipeline->data)->in, 0);
		only_cmd_pipe(pipeline, env);
	}
	if (((t_command *)pipeline->data)->out != 1)
		close(((t_command *)pipeline->data)->out);		
	if (((t_command *)pipeline->data)->in != 0)
		close(((t_command *)pipeline->data)->in);
}

void	only_cmd_pipe(t_list *pipeline, t_list **env)
{
	if (is_path_exist(pipeline, env) == TRUE)
		exec_cmd(((t_command *)(pipeline->data))->tokens, env, CNF);
	else if (is_path_exist(pipeline, env) == 2)
		exec_builtin(((t_command *)pipeline->data)->tokens, env, 1);
	else if (is_path_exist(pipeline, env) == FALSE)
	{
		if (is_builtin(((t_command *)(pipeline->data))->tokens) == 1)
			exec_cmd(((t_command *)(pipeline->data))->tokens, env, NSFD);
		else
			exec_builtin(((t_command *)(pipeline->data))->tokens, env, 1);
	}
}

void	ft_pipe_cmd_redir(t_list *pipeline, t_list **env)
{
	g_vars.pid = fork();
	if (g_vars.pid < 0)
		exit(1);
	if (g_vars.pid == 0)
	{
		if (((t_command *)pipeline->data)->out != 1)
		{
			dup2(((t_command *)pipeline->data)->out, 1);
			if (pipeline->next)
				close(((t_command *)pipeline->next->data)->in);
		}
		if (((t_command *)pipeline->data)->in != 0)
			dup2(((t_command *)pipeline->data)->in, 0);
		ft_exec_pipe_redir(pipeline, env);
	}
	if (((t_command *)pipeline->data)->out != 1)
		close(((t_command *)pipeline->data)->out);
	if (((t_command *)pipeline->data)->in != 0)
		close(((t_command *)pipeline->data)->in);
}

void	ft_exec_pipe_redir(t_list *pipeline, t_list **env)
{
	check_errors(((t_command *)(pipeline->data))->redir);
	((t_command *)(pipeline->data))->redir =
		ft_hook(((t_command *)(pipeline->data))->redir);
	if (is_path_exist(pipeline, env) == TRUE)
	{		
		ft_is_redirection(((t_command *)(pipeline->data))->redir, 1);
		exec_cmd(((t_command *)(pipeline->data))->tokens, env, CNF);
	}
	else if(is_path_exist(pipeline, env) == 2)
	{
		ft_is_redirection(((t_command *)(pipeline->data))->redir, 1);
		exec_builtin(((t_command *)(pipeline->data))->tokens, env, 1);
	}
	else if (is_path_exist(pipeline, env) == 3)
	{
		ft_is_redirection(((t_command *)(pipeline->data))->redir, 2);
		exit(g_vars.i);
	}
	else
		ft_exec_pipe_redir_2(pipeline, env);
}

void	ft_exec_pipe_redir_2(t_list *pipeline, t_list **env)
{
	if (is_builtin(((t_command *)(pipeline->data))->tokens) == 2)
	{
		ft_is_redirection(((t_command *)(pipeline->data))->redir, 0);
		return ;
	}
	else
		ft_is_redirection(((t_command *)(pipeline->data))->redir, 1);
	if (is_builtin(((t_command *)(pipeline->data))->tokens) == 1)
		exec_cmd(((t_command *)(pipeline->data))->tokens, env, NSFD);
	else if (is_builtin(((t_command *)(pipeline->data))->tokens) == 0)
		exec_builtin(((t_command *)(pipeline->data))->tokens, env, 1);
	
}

void	ft_pipe(t_list *pipeline)
{
	int		pipes[2];

	if (((t_command *)(pipeline->data))->out == 666)
	{
		pipe(pipes);
		((t_command *)(pipeline->data))->out = pipes[1];
		((t_command *)(pipeline->next->data))->in = pipes[0];
	}
}

void	ft_pipes_loop(t_wrapper *wrp)
{
	int		stats;
	t_list	*tmp;

	stats = 0;
	tmp = wrp->pipeline;
	while (tmp)
	{
		ft_pipe(tmp);
		if (!(((t_command *)(tmp->data))->redir))
			ft_pipe_cmd_only(tmp, &wrp->env);
		else
			ft_pipe_cmd_redir(tmp, &wrp->env);
		if (tmp->next == NULL)
			break;
		tmp = tmp->next;
	}
	while (waitpid(-1, &stats, 0)> 0)
	{
		if (WIFEXITED(stats))
			g_vars.i = WEXITSTATUS(stats);
	}
}