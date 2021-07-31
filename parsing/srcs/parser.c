/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 10:30:12 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/28 15:21:59 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parser(t_wrapper *wrp, char **envp)
{
	t_pipeline	*tmp;
	int 		tmpi;

	wrp->env = NULL;
	wrp->env = init_env(envp, wrp->env);
	while (1)
	{
		tmpi = parser_line(wrp);
		
		ft_open_heredoc(wrp);
		if (tmpi == 1)
		{	
			g_variables.i = 0;
			if (wrp->pipeline->next == NULL && !wrp->pipeline->redir)
				ft_only_cmd(wrp, 0);
			else if (wrp->pipeline->next == NULL && wrp->pipeline->redir)
				ft_redir_cmd(wrp, 0);
			else if (wrp->pipeline->next)
			{
				tmp = wrp->pipeline;
				while (tmp != NULL)
				{
					if (tmp->next != NULL)
					{
						tmp->next->in = 666;
						tmp->out = 666;
					}
					tmp = tmp->next;
				}
				ft_pipes_loop(wrp);
			}
		}
	}
}

static void	norme_parser_tokens(t_wrapper *wrp, char
**tab, int i, t_iofiles *iofiles)
{
	char	**tmp;
	t_cmd	token;

	while (tab[i])
	{
		if (ft_strncmp(tab[i], "export", 6) && ft_strncmp(tab[i], "<<", 2))
			tab[i] = quotes_reformat(tab[i]);
		tmp = ft_split(tab[i], ' ');
		if (ft_strcmp(tmp[0], "<<") && ft_strcmp(tmp[0], "export"))
			tab_trimmer(tmp);
		parser_tab_checker(tmp, iofiles);
		token = cmd_create(iofiles->tokens);
		pipeline_addback(&(wrp->pipeline), pipeline_new(token, iofiles->redir));
		i++;
	}
}

void	parser_tokens(t_wrapper *wrp, char *line)
{
	char		**tab;
	int			i;
	t_iofiles	*iofiles;

	i = 0;
	tab = ft_split2(line, '|');
	//debug_tab(tab);
	if (!tab || *tab == NULL)
		return ;
	iofiles = (t_iofiles *)malloc(sizeof(t_iofiles));
	wrp->pipeline = NULL;
	iofiles = (t_iofiles *)malloc(sizeof(t_iofiles));
	norme_parser_tokens(wrp, tab, i, iofiles);
	destroy_tab(tab);
}

int	parser_line(t_wrapper *wrp)
{
	char	*line;

	(void)wrp;
	usleep (100000);
	line = readline(BHBLU "petitshell-1.0" reset BHWHT "$ " reset);
	if (line && *line)
		add_history (line);
 	if (line && line[0] == 0)
	 	return (0);
	if (!line)
	{	
		ft_putendl_fd("exit", 2);
		exit(0);
	}
	line = reformat_line(wrp, line);
	if (line == NULL)
	{
		put_err(wrp);
		return (0);
	}
	else
	{
		parser_tokens(wrp, line);
		free(line);
		line = NULL;
		return (1);
	}
}
