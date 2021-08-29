/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:58:12 by oel-yous          #+#    #+#             */
/*   Updated: 2021/08/29 16:34:34 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_dup_out_redir(t_list *redir, int file)
{
	if (((t_redir *)redir->data)->type == 3)
	{
		file = open(((t_redir *)redir->data)->filename, O_WRONLY | O_TRUNC);
		dup2(file, 1);
		close(file);
		if (g_vars.i == 123)
			exit(1);
	}
	else if (((t_redir *)redir->data)->type == 4)
	{
		file = open(((t_redir *)redir->data)->filename,
			O_WRONLY | O_APPEND, 0644);
		dup2(file, 1);
		close (file);
		if (g_vars.i == 123)
			exit(1);
	}
}
void	ft_is_redirection(t_list *redir)
{
	int		file;

	while (redir != NULL)
	{
		if (((t_redir *)redir->data)->type == 1)
		{
			file = open(((t_redir *)redir->data)->filename, O_RDONLY);
			dup2(file, 0);
			close(file);
			if (!ft_strncmp(((t_redir *)redir->data)->filename, "/tmp/", 5))
				unlink(((t_redir *)redir->data)->filename);			
			if (g_vars.i == 123)
				exit(1);
		}
		else
		{
			ft_dup_out_redir(redir, file);
		}
		if (redir->next != NULL)
			redir = redir->next;
		else
			break;
	}
}

void	ft_in_redir(t_list *redir)
{
	int			in;

	in = open(((t_redir *)redir->data)->filename, O_RDONLY);
	if (in == -1)
	{
		ft_putstr_fd("petitshell: ", 2);
		perror(((t_redir *)redir->data)->filename);
		g_vars.i = 123;
	}
	close(in);
}

void	ft_out_redir(t_list *redir)
{
	int			out;

	out = open(((t_redir *)redir->data)->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out == -1)
	{
		ft_putstr_fd("petitshell: ", 2);
		perror(((t_redir *)redir->data)->filename);
		g_vars.i = 123;
	}
	close (out);
}

void	ft_append_redir(t_list *redir)
{
	int			out;

	out = open(((t_redir *)redir->data)->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (out == -1)
	{
		ft_putstr_fd("petitshell: ", 2);
		perror(((t_redir *)redir->data)->filename);
		g_vars.i = 123;
	}
	close(out);
}
