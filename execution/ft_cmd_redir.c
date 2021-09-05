/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:53:35 by oel-yous          #+#    #+#             */
/*   Updated: 2021/09/04 11:00:12 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_redir_cmd(t_wrapper *wrp)
{
	check_errors(((t_command *)wrp->pipeline->data)->redir);
	((t_command *)wrp->pipeline->data)->redir
		= ft_hook((((t_command *)(wrp->pipeline->data))->redir));
	if (is_path_exist(wrp->pipeline, &wrp->env) == TRUE)
		exec_cmd_redir(wrp);
	else if (is_path_exist(wrp->pipeline, &wrp->env) == 2)
		exec_builtin_redir(wrp);
	else if (is_path_exist(wrp->pipeline, &wrp->env) == 3)
		ft_is_redirection(
			(((t_command *)(wrp->pipeline->data))->redir), 0);
	else
		unset_path_redir(wrp);
}

void	unset_path_redir(t_wrapper *wrp)
{
	int		stats;

	stats = 0;
	if (is_builtin(((t_command *)wrp->pipeline->data)->tokens) == 1)
	{
		g_vars.pid = fork();
		if (g_vars.pid < 0)
			exit(1);
		if (g_vars.pid == 0)
		{
			ft_is_redirection(
				(((t_command *)(wrp->pipeline->data))->redir), 1);
			exec_cmd(((t_command *)wrp->pipeline->data)->tokens,
				&wrp->env, NSFD);
		}
		waitpid(g_vars.pid, &stats, 0);
		if (WIFEXITED(stats))
			g_vars.i = WEXITSTATUS(stats);
	}
	else if (!is_builtin(((t_command *)wrp->pipeline->data)->tokens))
		ft_unset_path_builtin(wrp, stats);
	else
		ft_is_redirection(
			(((t_command *)(wrp->pipeline->data))->redir), 0);
}

void	ft_unset_path_builtin(t_wrapper *wrp, int stats)
{
	g_vars.pid = fork();
	if (g_vars.pid < 0)
		exit(1);
	if (g_vars.pid == 0)
	{
		ft_is_redirection(
			(((t_command *)(wrp->pipeline->data))->redir), 1);
		exec_builtin(
			((t_command *)wrp->pipeline->data)->tokens, &wrp->env, 1);
	}
	waitpid(g_vars.pid, &stats, 0);
	if (WIFEXITED(stats))
		g_vars.i = WEXITSTATUS(stats);
}

void	exec_cmd_redir(t_wrapper *wrp)
{
	int		stats;

	stats = 0;
	g_vars.pid = fork();
	if (g_vars.pid < 0)
		exit(1);
	if (g_vars.pid == 0)
	{
		ft_is_redirection(
			(((t_command *)(wrp->pipeline->data))->redir), 1);
		exec_cmd(
			((t_command *)wrp->pipeline->data)->tokens, &wrp->env, CNF);
	}
	waitpid(g_vars.pid, &stats, 0);
	if (WIFEXITED(stats))
		g_vars.i = WEXITSTATUS(stats);
}

void	exec_builtin_redir(t_wrapper *wrp)
{
	int		stats;

	stats = 0;
	g_vars.pid = fork();
	if (g_vars.pid < 0)
		exit(1);
	if (g_vars.pid == 0)
	{
		ft_is_redirection(
			(((t_command *)(wrp->pipeline->data))->redir), 1);
		exec_builtin(
			((t_command *)wrp->pipeline->data)->tokens, &wrp->env, 1);
	}
	waitpid(g_vars.pid, &stats, 0);
	if (WIFEXITED(stats))
		g_vars.i = WEXITSTATUS(stats);
}
