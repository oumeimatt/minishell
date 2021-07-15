/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 10:30:12 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/15 13:12:26 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void		parser(t_wrapper *wrp, char **envp)
{
	t_pipeline *tmp;

	wrp->env = NULL;
	wrp->env = init_env(envp, wrp->env);
	while (1)
	{
		if (parser_line(wrp))
		{	
			g_i = 0;
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
			//printf("%d\n", g_i);
		}
	}
}

void			parser_tokens(t_wrapper *wrp, char *line)
{
	char	**tab;
	int		i;
	char	**tmp;
	t_iofiles *iofiles;
	t_cmd	token;

	i = 0;
	tab = ft_split2(line, '|');
	if (!tab || *tab == NULL)
		return ;
 	printf("Debug_tab(tab) :");
	debug_tab(tab);
	iofiles = (t_iofiles *)malloc(sizeof(t_iofiles));
	wrp->pipeline = NULL;
	iofiles = (t_iofiles *)malloc(sizeof(t_iofiles));
	while (tab[i])
	{
		if (ft_strncmp(tab[i], "export", 6) && ft_strncmp(tab[i], "<<", 2))
			tab[i] = quotes_reformat(tab[i]);
		tmp = ft_split(tab[i], ' ');
 		printf ("Debug_tab(tmp) : ");debug_tab(tmp);
		if (ft_strcmp(tmp[0], "<<") && ft_strcmp(tmp[0], "export"))
			tab_trimmer(tmp);
		parser_tab_checker(wrp ,tmp, iofiles);
		token = cmd_create(iofiles->tokens);
 		pipeline_addback(&(wrp->pipeline), pipeline_new(token, iofiles->redir));
		i++;
	}
	destroy_tab(tab);
}

int				parser_line(t_wrapper *wrp)
{
	char	*line;

	usleep (100000);
	line = readline(BHBLU "petitshell-1.0" reset BHWHT "$ " reset);
	if (line && *line)
		add_history (line);
/* 	if (!line)
		printf("here!"); */
 	printf ("Line : %s\n", line);
	line = reformat_line(wrp, line);
	printf("Reformatted line : %s\n", line);
	if (line == NULL)
	{
		put_err(wrp);
		return (0);
	}
	else
	{
	//	exit(0);
		parser_tokens(wrp, line);
		printf("Pipeline_debug : ");
		pipeline_debug(wrp->pipeline);
/*  		if (wrp->pipeline->redir)	
			lstredir_debug(wrp->pipeline->redir); */
		free(line);
		line = NULL;
		return (1);
	}
}

