/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 10:30:12 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/09 21:49:40 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void		parser(t_wrapper *wrp, char **envp)
{
	wrp->env = NULL;
	wrp->env = init_env(envp, wrp->env);

	while (1)
	{
		parse_line(wrp);
		if (wrp->pipeline)
		{
			if (wrp->pipeline->next == NULL && !wrp->pipeline->redir)
				ft_only_cmd(wrp);	
			else if (wrp->pipeline->next == NULL && wrp->pipeline->redir)
				ft_redir_cmd(wrp);
		}
	}
}

void			parse_tokens(t_wrapper *wrp, char *line)
{
	char	**tab;
	int		i;
	char	**tmp;
	t_iofiles *iofiles;
	t_cmd	token;

	i = 0;

	line = ft_strtrim(line, " \t");
	tab = ft_split2(line, '|');
	if (!tab)
		return ;
	iofiles = (t_iofiles *)malloc(sizeof(t_iofiles));
	wrp->pipeline = NULL;
	iofiles = (t_iofiles *)malloc(sizeof(t_iofiles));
	while (tab[i])
	{
		tmp = ft_split(tab[i], ' ');
		tab_trimmer(tmp);
		tab_checker(wrp ,tmp, iofiles);
		token = cmd_create(iofiles->tokens);
 		pipeline_addback(&(wrp->pipeline), pipeline_new(token, iofiles->redir));
		i++;
	}
	destroy_tab(tab);
//	cmd_destroy(&token);
}

void			parse_line(t_wrapper *wrp)
{
	char	*line;

	usleep (100000);
	line = readline(">$ ");
	add_history (line);
	if (line != NULL)
	{
		parse_tokens(wrp, line);
//		pipeline_debug(wrp->pipeline); 
/* 		if (wrp->pipeline->redir)	
			lstredir_debug(wrp->pipeline->redir); */

		free(line);
		line = NULL;
	}
}