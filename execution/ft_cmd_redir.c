/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:53:35 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/12 18:01:31 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_redir_cmd(t_wrapper *wrp, int i)
{
	char	*path;
	char	**split_path;

	path = get_path(wrp->env);
    if (wrp->pipeline->redir->type == 2)
		ft_here_doc(wrp->pipeline->redir);
	if (path != NULL)
	{
		split_path = ft_split_2(path, ':');	
		if (is_builtin(wrp->pipeline->cmd.tokens) == 1)
            exec_cmd_redir(wrp, split_path, i);
		else
		{
			if (i == 0)
           		exec_builtin_redir(wrp);
		}
	}
	else
	{
		if (i == 0)
        	unset_path_redir(wrp, 0);
		else
			unset_path_redir(wrp, 1);
	}
}

void    unset_path_redir(t_wrapper *wrp, int i)
{
    pid_t   pid;
	int		stats;

	if (is_builtin(wrp->pipeline->cmd.tokens) == 1)
	{
		pid = fork();
		if (pid < 0)
			exit(1);
		if (pid == 0)
		{
			ft_is_redirection(wrp->pipeline->redir, 0);
			if (execve(wrp->pipeline->cmd.tokens[0], wrp->pipeline->cmd.tokens, NULL) == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(wrp->pipeline->cmd.tokens[0], 2);
				ft_putendl_fd(": No such file or directory", 2);
				exit(127);
			}
		}
		waitpid(pid, &stats, 0);
		if (WIFEXITED(stats))
			g_i = WEXITSTATUS(stats);
	}
	else
	{
		if (i == 0)
		{
			pid = fork();
			if (pid < 0)
				exit(1);
			if (pid == 0)
			{
				ft_is_redirection(wrp->pipeline->redir, 0);
				exec_builtin(wrp->pipeline->cmd.tokens, wrp->env, 1);
			}
		}
		else
		{
			ft_is_redirection(wrp->pipeline->redir, 0);
			exec_builtin(wrp->pipeline->cmd.tokens, wrp->env, 1);
		}
	}
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
			ft_is_redirection(wrp->pipeline->redir, 0);
			exec_cmd(wrp->pipeline->cmd.tokens);
		}
		waitpid(pid, &stats, 0);
		if (WIFEXITED(stats))
			g_i = WEXITSTATUS(stats);
	}
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
		ft_is_redirection(wrp->pipeline->redir, 0);
		exec_builtin(wrp->pipeline->cmd.tokens, wrp->env, 1);
	}
	waitpid(pid, &stats, 0);
	if (WIFEXITED(stats))
		g_i = WEXITSTATUS(stats);
}
