/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:58:12 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/09 16:50:24 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_is_redirection(t_lstredir *redir, int i)
{
	t_lstredir *tmp;

	tmp = redir;
	while (tmp != NULL)
	{
		if (tmp->next == NULL)
		{
			if (tmp->type == 1)
				ft_in_redir(tmp, i);
			else if (tmp->type == 2)
				ft_hd_redir(i);
			else if (tmp->type == 3)
				ft_out_redir(tmp, i);
			else if (tmp->type == 4)
				ft_append_redir(tmp, i);
			break;
		}
		if (tmp->type == 1)
			ft_in_redir(tmp, i);
		else if (tmp->type == 2)
			ft_hd_redir(i);
		else if (tmp->type == 3)
			ft_out_redir(tmp, i);
		else if (tmp->type == 4)
			ft_append_redir(tmp, i);
		tmp = tmp->next;
	}
}

void	ft_in_redir(t_lstredir *redir, int i)
{
	int			in;
	t_lstredir	*tmp;

	tmp = redir;
	in = open(tmp->filename, O_RDONLY);
	if (in == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(tmp->filename);
		exit(1);
	}
	if (i == 0)
	{
		dup2(in, 0);
		close(in);
	}
	else
		close(in);
}

void	ft_out_redir(t_lstredir *redir, int i)
{
	int			out;
	t_lstredir	*tmp;

	tmp = redir;
	out = open(tmp->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(tmp->filename);
		exit(1);
	}
	if (i == 0)
	{
		dup2(out, 1);
		close (out);
	}
	else
		close(out);
}

void	ft_append_redir(t_lstredir *redir, int i)
{
	int			out;
	t_lstredir *tmp;

	tmp = redir;
	out = open(tmp->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (out == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(tmp->filename);
		exit(1);
	}
	if (i == 0)
	{
		dup2(out, 1);
		close(out);
	}
	else
		close(out);
}
