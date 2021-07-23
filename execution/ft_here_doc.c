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

void	ft_here_doc(t_wrapper *wrp, char *filename)
{
	int			in;
	char		*delimiter;
	char		*line;
	int			expand;

	unlink(filename);
	in = open(filename, O_RDONLY | O_WRONLY | O_CREAT, 0644);
	delimiter = check_quotes(wrp->pipeline->redir->filename);
	expand = 1;
	if (ft_strcmp(delimiter, wrp->pipeline->redir->filename))
		expand = 0;
	ft_putendl_fd(delimiter, 2);
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

void	ft_open_heredoc(t_wrapper *wrp)
{
	t_wrapper	*tmp;
	char		*filename;

	tmp = wrp;
	while (tmp->pipeline)
	{
		filename = ft_random_name();
		while (tmp->pipeline->redir != NULL)
		{
			if (tmp->pipeline->redir->type == 2)
			{
				ft_here_doc(tmp, filename);
				tmp->pipeline->redir->type = 1;
				tmp->pipeline->redir->filename = ft_strdup(filename);
				free(filename);
				filename = NULL;
			}
			if (tmp->pipeline->redir->next != NULL)
				tmp->pipeline->redir = tmp->pipeline->redir->next;
			else
				break;
		}
		if (tmp->pipeline->next != NULL)
			tmp->pipeline = tmp->pipeline->next;
		else
			break;
	}
}

char	*ft_random_name(void)
{
	static int	nb = 0;
	char		*name;
	char		*str_nb;
	char		*str_modulo;
	char		*tmp;

	nb++;
	str_nb = ft_itoa(nb);
	str_modulo = ft_itoa(nb % 3);
	tmp = ft_strdup("/tmp/");
	tmp = ft_strjoin(tmp, str_nb);
	name = ft_strjoin(tmp, str_modulo);
	free(str_nb);
	free(str_modulo);
	return (name);
}