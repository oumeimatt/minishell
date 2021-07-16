/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:58:12 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/16 16:50:04 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_is_redirection(t_lstredir *redir)
{
	int		file;

	if (redir->type == 1)
	{
		file = open(redir->filename, O_RDONLY);
		dup2(file, 0);
		close(file);
		if (g_i == 123)
			exit(1);
	}
	else if (redir->type == 2)
	{
		file = open("/tmp/helper", O_RDONLY);
		dup2(file, 0);
		close(file);
	}
	else if (redir->type == 3)
	{
		file = open(redir->filename, O_WRONLY | O_TRUNC);
		dup2(file, 1);
		close (file);
		if (g_i == 123)
			exit(1);
	}
	else if (redir->type == 4)
	{
		file = open(redir->filename, O_WRONLY | O_APPEND, 0644);
		dup2(file, 1);
		close (file);
		if (g_i == 123)
			exit(1);
	}
}

void	ft_in_redir(t_lstredir *redir)
{
	int			in;

	in = open(redir->filename, O_RDONLY);
	if (in == -1)
	{
		ft_putstr_fd("petitshell: ", 2);
		perror(redir->filename);
		g_i = 123;
	}
	close(in);
}

void	ft_out_redir(t_lstredir *redir)
{
	int			out;

	out = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out == -1)
	{
		ft_putstr_fd("petitshell: ", 2);
		perror(redir->filename);
		g_i = 123;
	}
	close (out);
}

void	ft_append_redir(t_lstredir *redir)
{
	int			out;

	out = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (out == -1)
	{
		ft_putstr_fd("petitshell: ", 2);
		perror(redir->filename);
		g_i = 123;
	}
	close(out);
}
