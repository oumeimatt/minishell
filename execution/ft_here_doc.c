/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:50:02 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/09 16:50:49 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_hd_redir(int i)
{
	int 		in;

	in = open("/tmp/helper", O_RDONLY);
	if (i == 0)
		dup2(in, 0);
	close(in);
	unlink("/tmp/helper");
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
