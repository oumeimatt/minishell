/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:58:12 by oel-yous          #+#    #+#             */
/*   Updated: 2021/09/04 11:08:18 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_dup_out_redir(t_list *redir, int file, int i)
{
	if (((t_redir *)redir->data)->type == 3)
	{
		file = open(((t_redir *)redir->data)->filename, O_WRONLY | O_TRUNC);
		if (i == 1)
			dup2(file, 1);
		close(file);
		if (g_vars.i == 123 && i == 1)
			exit(1);
		if (g_vars.i == 123)
			g_vars.i = 1;
	}
	else if (((t_redir *)redir->data)->type == 4)
	{
		file = open(((t_redir *)redir->data)->filename,
				O_WRONLY | O_APPEND, 0644);
		if (i == 1)
			dup2(file, 1);
		close (file);
		if (g_vars.i == 123 && i == 1)
			exit(1);
		if (g_vars.i == 123)
			g_vars.i = 1;
	}
}

void	ft_is_redirection(t_list *redir, int i)
{
	int		file;

	while (redir != NULL)
	{
		if (((t_redir *)redir->data)->type == 1)
		{
			file = open(((t_redir *)redir->data)->filename, O_RDONLY);
			if (i == 1)
				dup2(file, 0);
			close(file);
			if (!ft_strncmp(((t_redir *)redir->data)->filename, "/tmp/", 5))
				unlink(((t_redir *)redir->data)->filename);
			if (g_vars.i == 123 && i == 1)
				exit(1);
			if (g_vars.i == 123)
				g_vars.i = 1;
		}
		else
			ft_dup_out_redir(redir, file, i);
		if (redir->next != NULL)
			redir = redir->next;
		else
			break ;
	}
}
