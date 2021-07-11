/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 10:30:12 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/11 17:06:35 by ztaouil          ###   ########.fr       */
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
			if (wrp->pipeline)
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
	iofiles = (t_iofiles *)malloc(sizeof(t_iofiles));
	wrp->pipeline = NULL;
	iofiles = (t_iofiles *)malloc(sizeof(t_iofiles));
	while (tab[i])
	{
		tmp = ft_split(tab[i], ' ');
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
	line = readline(">$ ");
	add_history (line);
	line = reformat_line(wrp, line);
	if (line == NULL)
	{
		put_err(wrp);
		return (0);
	}
	else
	{
		parser_tokens(wrp, line);
/* 		pipeline_debug(wrp->pipeline); 		
 		if (wrp->pipeline->redir)	
			lstredir_debug(wrp->pipeline->redir); */
		free(line);
		line = NULL;
		return (1);
	}
}

char 		*reformat_line(t_wrapper *wrp, char *line)
{
	int flag;
	
	line = redirection_reformat(line);
	line = pipes_reformat(line);
	line = expand_env(wrp, line);
	line = ft_strtrim(line, "\t ");
	flag = check_line_syntax(line);
	if (flag <= 0)
	{
		load_msg_err(wrp, flag);
		free(line);
		line = NULL;
	}
	return (line);
}

int			check_line_syntax(char *string)
{
	int	s_count;
	int len;
	
	s_count = 0;
	len = ft_strlen(string);
	if ((!ft_strncmp(string, "\"", 1) && len < 2) || (!ft_strncmp(string, "\'", 1) && len < 2) || (string[len - 1] == '|' && len > 1))
		return (0);
	else if (!ft_strncmp(string, "|", 1))
		return (-1);
	while (string[s_count] != '\0')
	{
		s_count++;
	}
	return (1);
}