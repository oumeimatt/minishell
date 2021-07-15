/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:50:02 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/15 15:32:05 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_hd_redir()
{
	int 		in;

	in = open("/tmp/helper", O_RDONLY);
	dup2(in, 0);
	close(in);
	unlink("/tmp/helper");
}

void	ft_here_doc(t_wrapper *wrp)
{
	int			in;
	char		*delimiter;
	char		*line;
	int			expand;

	unlink("/tmp/helper");
	in = open("/tmp/helper", O_RDONLY | O_WRONLY | O_CREAT, 0644);
	delimiter = ft_strdup(wrp->pipeline->redir->filename);
	expand = 1;
	if (delimiter[0] == '\'' || delimiter[0] == '"')
	{
		delimiter = quotes_reformat(delimiter);
		expand = 0;
	}
	while (1)
	{
		line  = readline(">");
		if (expand == 1)
		{
			line = expand_exit_code(wrp, line);
			line = expand_env(wrp, line);
		}
		if (!ft_strcmp(line, delimiter))
			break;
		ft_putendl_fd(line, in);
		free(line);
		line = NULL;
	}
	free(delimiter);
	free(line);
	line = NULL;
	close(in);
}
