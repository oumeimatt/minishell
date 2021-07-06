/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 10:30:12 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/06 15:04:19 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void		parser(t_wrapper *wrp, char **envp)
{
	t_env *env;

	env = NULL;
	env = init_env(envp, env);
	while (1)
	{
		parse_line(wrp);
		is_builtin(wrp->pipeline->cmd.tokens, env);
	}
}

void			parse_tokens(t_wrapper *wrp, char *line)
{
	char	**tab;
	int		i;
	char	**tmp;
	t_iofiles iofiles;
	t_cmd	token;


	i = 0;

	line = ft_strtrim(line, " \t");
	tab = ft_split(line, '|');
	wrp->pipeline = NULL;
	while (tab[i])
	{
		tmp = ft_split(tab[i], ' ');
		tab_checker(wrp ,tmp, &iofiles);
		token = cmd_create(tmp, iofiles.infile, "test");
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