/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 10:30:12 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/12 16:24:56 by ztaouil          ###   ########.fr       */
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

void			parser_tokens(t_wrapper *wrp, char *line)
{
	char	**tab;
	int		i;
	char	**tmp;
	t_iofiles *iofiles;
	t_cmd	token;

	i = 0;
	tab = ft_split2(line, '|');
	if (!tab)
		return ;
	printf("debug_tab(tab) :"); debug_tab(tab);
	iofiles = (t_iofiles *)malloc(sizeof(t_iofiles));
	wrp->pipeline = NULL;
	iofiles = (t_iofiles *)malloc(sizeof(t_iofiles));
	while (tab[i])
	{
		tmp = ft_split(tab[i], ' ');
		printf ("deub_tab(tmp) : ");debug_tab(tmp);
/* 		if (ft_strcmp(tmp[0], "<<"))
			tab_trimmer(tmp); */
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
	const char *prompt;

	usleep (100000);
	prompt = get_prompt(wrp);	
	line = readline(prompt);
	add_history (line);
	printf ("Line : %s\n", line);
	line = reformat_line(wrp, line);printf("Reformatted line : %s\n", line);
	if (line == NULL)
	{
		put_err(wrp);
		return (0);
	}
	else
	{
	//	exit(0);
		parser_tokens(wrp, line);
		printf("pipeline_debug : ");pipeline_debug(wrp->pipeline);printf ("\n");
/*  		if (wrp->pipeline->redir)	
			lstredir_debug(wrp->pipeline->redir); */
		free(line);
		line = NULL;
		return (1);
	}
}

const char 			*get_prompt(t_wrapper *wrp)
{
	char *pwd = print_value(wrp->env, "PWD");
	const char *prompt = ft_strjoin(BHGRN, pwd);
	prompt = ft_strjoin(prompt, reset);
	prompt = ft_strjoin(prompt, BHRED);
	prompt = ft_strjoin(prompt, " >$ ");
	prompt = ft_strjoin(prompt, reset);
	return (prompt);
}