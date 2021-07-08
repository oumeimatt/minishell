/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:09:56 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/08 19:27:21 by oel-yous         ###   ########.fr       */
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
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
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
		if (is_builtin(wrp->pipeline->cmd.tokens, wrp->env) == 1)
		{
			wrp->pipeline->cmd.tokens[0] = 
				absolute_path(wrp->pipeline->cmd.tokens[0], split_path);
			pid = fork();
			if (pid < 0)
				exit(1);
			if (pid == 0)
				exec_cmd(wrp->pipeline->cmd.tokens);
			free(path);
		}
	}
	else
	{
		if (is_builtin(wrp->pipeline->cmd.tokens, wrp->env) == 1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(wrp->pipeline->cmd.tokens[0], 2);
			ft_putendl_fd(": No such file or directory", 2);
		}
	}
}

char	*find_limiter(t_lstredir *redir)
{
	t_lstredir	*tmp;
	char		*limiter;

	limiter = NULL;
	tmp = redir;
	while (tmp->next != NULL)
	{
		if (tmp->type == 2)
		{
			if (limiter != NULL)
			{
				free(limiter);
				limiter = NULL;
			}
			limiter = ft_strdup(tmp->filename);
		}
		tmp = tmp->next;
	}
	if (tmp->type == 2)
	{
		if (limiter != NULL)
		{
			free(limiter);
			limiter = NULL;
		}
		limiter = ft_strdup(tmp->filename);
	}
	return (limiter);
}
void	ft_here_doc(t_lstredir *redir)
{
	int			in;
	char		*limiter;
	char		*line;

	in = open("/tmp/helper", O_RDONLY | O_WRONLY | O_CREAT, 0644);
	limiter = find_limiter(redir);
	while (1)
	{
		line  = readline(">");
		if (ft_strcmp(line, limiter) == 0)
			break;
		ft_putendl_fd(line, in);
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	close(in);
}

void	ft_redir_cmd(t_wrapper *wrp)
{
	char	*path;
	char	**split_path;
	pid_t	pid;
	int		in;

	in = 0;
	path = get_path(wrp->env);
	if (path != NULL)
	{
		split_path = ft_split_2(path, ':');
		wrp->pipeline->cmd.tokens[0] = 
			absolute_path(wrp->pipeline->cmd.tokens[0], split_path);
		if (wrp->pipeline->redir->type == 2)
			ft_here_doc(wrp->pipeline->redir);
		pid = fork();
		if (pid < 0)
			exit(1);
		if (pid == 0)
		{
			ft_is_redirection(wrp->pipeline->redir, 0);
			if (is_builtin(wrp->pipeline->cmd.tokens, wrp->env) == 1)
				exec_cmd(wrp->pipeline->cmd.tokens);
		}
		
		free(path);
	}
	else
	{
		if (is_builtin(wrp->pipeline->cmd.tokens, wrp->env) == 1)
		{
			if (wrp->pipeline->redir->type == 2)
				ft_here_doc(wrp->pipeline->redir);
			ft_is_redirection(wrp->pipeline->redir, 1);
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(wrp->pipeline->cmd.tokens[0], 2);
			ft_putendl_fd(": No such file or directory", 2);
		}
	}
}