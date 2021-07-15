/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:53:35 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/15 19:39:30 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_lstredir	*ft_hook(t_lstredir *redir)
{
	while (redir != NULL)
	{
		if (redir->type == 1)
			ft_in_redir(redir);
		else if (redir->type == 3)
			ft_out_redir(redir);
		else if (redir->type == 4)
			ft_append_redir(redir);
		if (redir->next != NULL)
			redir = redir->next;
		else
			break;
	}
	return (redir);
}

void	ft_redir_cmd(t_wrapper *wrp, int i)
{
	char		*path;
	char		**split_path;
	
	path = get_path(wrp->env);
	wrp->pipeline->redir = ft_hook(wrp->pipeline->redir);
	if (path != NULL)
	{
		split_path = ft_split_2(path, ':');	
		if (is_builtin(wrp->pipeline->cmd.tokens) == 1)
            exec_cmd_redir(wrp, split_path, i);
		else
           	exec_builtin_redir(wrp);
	}
	else
        unset_path_redir(wrp);
}

void    unset_path_redir(t_wrapper *wrp)
{
	int		stats;

	stats = 0;
	wrp->pipeline->redir = ft_hook(wrp->pipeline->redir);
	if (is_builtin(wrp->pipeline->cmd.tokens) == 1)
	{
		wrp->pipeline->cmd.pid = fork();
		if (wrp->pipeline->cmd.pid < 0)
			exit(1);
		if (wrp->pipeline->cmd.pid == 0)
		{
			ft_is_redirection(wrp->pipeline->redir);
			if (execve(wrp->pipeline->cmd.tokens[0],
				wrp->pipeline->cmd.tokens, NULL) == -1)
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
	else
		ft_unset_path_builtin(wrp, stats);
}

void	ft_unset_path_builtin(t_wrapper *wrp, int stats)
{
	wrp->pipeline->cmd.pid = fork();
	if (wrp->pipeline->cmd.pid < 0)
		exit(1);
	if (wrp->pipeline->cmd.pid == 0)
	{
		ft_is_redirection(wrp->pipeline->redir);
		exec_builtin(wrp->pipeline->cmd.tokens, wrp->env, 1);
	}
	waitpid(wrp->pipeline->cmd.pid, &stats, 0);
	if (WIFEXITED(stats))
		g_i = WEXITSTATUS(stats);
}

void    exec_cmd_redir(t_wrapper *wrp, char **split_path, int i)
{
	pid_t	pid;
	int		stats;

    wrp->pipeline->cmd.tokens[0] = 
		absolute_path(wrp->pipeline->cmd.tokens[0], split_path);
	if (i == 0)
	{
		pid = fork();
		if (pid < 0)
			exit(1);
		if (pid == 0)
		{
			ft_is_redirection(wrp->pipeline->redir);
			exec_cmd(wrp->pipeline->cmd.tokens);
		}
		waitpid(pid, &stats, 0);
		if (WIFEXITED(stats))
			g_i = WEXITSTATUS(stats);
	}
	else
		exec_cmd(wrp->pipeline->cmd.tokens);
}

void    exec_builtin_redir(t_wrapper *wrp)
{
    pid_t   pid;
	int		stats;

	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
	{
		ft_is_redirection(wrp->pipeline->redir);
		exec_builtin(wrp->pipeline->cmd.tokens, wrp->env, 1);
	}
	waitpid(pid, &stats, 0);
	if (WIFEXITED(stats))
		g_i = WEXITSTATUS(stats);
}
