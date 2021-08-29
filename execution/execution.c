/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 09:08:08 by oel-yous          #+#    #+#             */
/*   Updated: 2021/08/29 14:52:44 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_vars	g_vars;

void	execute(t_wrapper *wrp)
{
	t_list	*tmp;

	g_vars.pid = 0;
	g_vars.i = 0;
	ft_open_heredoc(wrp);
	if (!wrp->pipeline->next && !((t_command *)(wrp->pipeline->data))->redir)
		ft_only_cmd(wrp, 0);
	if (!wrp->pipeline->next && ((t_command *)(wrp->pipeline->data))->redir)
		ft_redir_cmd(wrp, 0);
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