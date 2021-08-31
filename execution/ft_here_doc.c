/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:50:02 by oel-yous          #+#    #+#             */
/*   Updated: 2021/08/30 18:13:15 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int		check_for_heredoc(t_wrapper *wrp)
{
	t_list	*tmp;
	t_list	*redtmp;

	tmp = wrp->pipeline;
	while(tmp != NULL)
	{
		redtmp = ((t_command *)(tmp->data))->redir;
		while (redtmp != NULL)
		{
			if (((t_redir *)(redtmp->data))->type == 2)
				return (1);
			if (redtmp->next != NULL)
				redtmp = redtmp->next;
			else
				break;
		}
		if (tmp->next != NULL)
			tmp = tmp->next;
		else
			break;
	}
	return (0);
}
void	ft_here_doc(t_wrapper *wrp, char *filename, t_list *redir)
{
	int			in;
	char		*delimiter;
	char		*line;
	int			expand;

	in = open(filename, O_RDONLY | O_WRONLY | O_CREAT, 0644);
	delimiter = check_quotes(((t_redir *)redir->data)->filename);
	expand = 1;
	if (ft_strcmp(delimiter, ((t_redir *)redir->data)->filename))
		expand = 0;
	ft_putendl_fd(delimiter, 2);
	while (1)
	{
		line  = readline(">");
		if (expand == 1)
		{
			line = expand_exit_code(line);
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
	t_list	*tmp;
	t_list	*tmpredir;
	char		*filename;

	tmp = wrp->pipeline;
	filename = NULL;
	if (check_for_heredoc(wrp) == 1)
	{
		while (tmp != NULL)
		{
			tmpredir = ((t_command *)(tmp->data))->redir;
			while (tmpredir != NULL)
			{
				if (((t_redir *)tmpredir->data)->type == 2)
				{
					filename = ft_random_name(filename);
					ft_putendl_fd("=========", 2);
					ft_putendl_fd(filename, 2);
					ft_putendl_fd("=========", 2);
					ft_here_doc(wrp, filename, tmpredir);
					((t_redir *)tmpredir->data)->type = 1;
					((t_redir *)tmpredir->data)->filename = ft_strdup(filename);
				}
				if (tmpredir->next != NULL)
					tmpredir = tmpredir->next;
				else
				{
					free(filename);
					filename = NULL;
					break;
				}
			}
			if (tmp->next != NULL)
				tmp = tmp->next;
			else
				break;
		}
	}
}

char	*ft_random_name(char *filename)
{
	static int	nb = 0;
	char		*name;
	char		*str_nb;
	char		*str_modulo;
	char		*tmp;

	if (filename != NULL)
	{
		unlink(filename);
		free(filename);
		filename = NULL;
	}
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