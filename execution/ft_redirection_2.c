/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 10:49:08 by oel-yous          #+#    #+#             */
/*   Updated: 2021/09/04 19:22:51 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_append_redir(t_list *redir)
{
	int	out;

	out = open(((t_redir *)redir->data)->filename,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (out == -1)
	{
		ft_putstr_fd("petitshell: ", 2);
		perror(((t_redir *)redir->data)->filename);
		g_vars.i = 123;
	}
	close(out);
}

void	ft_out_redir(t_list *redir)
{
	int	out;

	out = open(((t_redir *)redir->data)->filename,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out == -1)
	{
		ft_putstr_fd("petitshell: ", 2);
		perror(((t_redir *)redir->data)->filename);
		g_vars.i = 123;
	}
	close (out);
}

void	ft_in_redir(t_list *redir)
{
	int	in;

	in = open(((t_redir *)redir->data)->filename, O_RDONLY);
	if (in == -1)
	{
		if (!ft_strncmp(((t_redir *)redir->data)->filename, "/tmp/", 5))
			return ;
		ft_putstr_fd("petitshell: ", 2);
		perror(((t_redir *)redir->data)->filename);
		g_vars.i = 123;
	}
	close(in);
}

void	check_errors(t_list *redir)
{
	t_list	*tmp;

	tmp = redir;
	while (tmp != NULL)
	{
		if (((t_redir *)tmp->data)->type == 1 && g_vars.i != 123)
			ft_in_redir(tmp);
		else if (((t_redir *)tmp->data)->type == 3 && g_vars.i != 123)
			ft_out_redir(tmp);
		else if (((t_redir *)tmp->data)->type == 4 && g_vars.i != 123)
			ft_append_redir(tmp);
		if (tmp->next != NULL)
			tmp = tmp->next;
		else
			break ;
	}
}

void	free_strs(char *str1, char *str2)
{
	free(str1);
	str1 = NULL;
	free(str2);
	str2 = NULL;
}
