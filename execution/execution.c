/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 09:08:08 by oel-yous          #+#    #+#             */
/*   Updated: 2021/08/31 16:17:51 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_print_error(char **wrng_cmd, char *error)
{
	ft_putstr_fd("petitshell: ", 2);
	ft_putstr_fd(wrng_cmd[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error, 2);
}

int		is_path_exist(t_wrapper *wrp)
{
	char	*path;

	if (is_builtin(((t_command *)(wrp->pipeline->data))->tokens) == 1)
	{
		path = get_value_env(&wrp->env, "PATH");
		if (path != NULL)
		{
			((t_command *)(wrp->pipeline->data))->tokens[0] =
				ft_cmd_path(((t_command *)(wrp->pipeline->data))->tokens[0],
					path);
			return (TRUE);
		}
		else
			return (FALSE);
	}
	else if (is_builtin(((t_command *)(wrp->pipeline->data))->tokens) == 2) // cmd = NULL
		return (3);
	return (2); // cmd is builtin;
}

void	execute(t_wrapper *wrp)
{
	t_list	*tmp;

	g_vars.pid = 0;
	g_vars.i = 0;
	ft_open_heredoc(wrp);
	if (!wrp->pipeline->next && !((t_command *)(wrp->pipeline->data))->redir)
		ft_only_cmd(wrp);
	if (!wrp->pipeline->next && ((t_command *)(wrp->pipeline->data))->redir)
		ft_redir_cmd(wrp);
	else if (wrp->pipeline->next)
	{
		tmp = wrp->pipeline;
		while (tmp != NULL)
		{
			if (tmp->next != NULL)
			{
				((t_command *)tmp->next->data)->in = 666;
				((t_command *)tmp->data)->out = 666;
			}
			tmp = tmp->next;
		}
		ft_pipes_loop(wrp);
	}
}