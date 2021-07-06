/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 10:30:12 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/06 20:44:38 by ztaouil          ###   ########.fr       */
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
			is_builtin(wrp->pipeline->cmd.tokens, wrp->env);
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

	iofiles = (t_iofiles *)malloc(sizeof(t_iofiles));
	line = ft_strtrim(line, " \t");
	tab = ft_split(line, '|');
	
	wrp->pipeline = NULL;
	while (tab[i])
	{
		tmp = ft_split(tab[i], ' ');
		tab_checker(wrp ,tmp, iofiles);
		tab_trimmer(iofiles->tokens);
		token = cmd_create(iofiles->tokens, iofiles->infile, iofiles->outfile);
		pipeline_addback(&(wrp->pipeline), pipeline_new(token));
		i++;
	}
	destroy_tab(tab);
//	cmd_destroy(&token);
}

void			parse_line(t_wrapper *wrp)
{
	char	*line;

	line = readline(">$ ");
	add_history (line);
	if (line != NULL)
	{
		parse_tokens(wrp, line);
		pipeline_debug(wrp->pipeline);		
		free(line);
		line = NULL;
	}
}