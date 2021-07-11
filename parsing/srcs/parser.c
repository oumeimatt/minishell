/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 10:30:12 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/11 20:01:40 by ztaouil          ###   ########.fr       */
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
	debug_tab(tab);
	iofiles = (t_iofiles *)malloc(sizeof(t_iofiles));
	wrp->pipeline = NULL;
	iofiles = (t_iofiles *)malloc(sizeof(t_iofiles));
	while (tab[i])
	{
		tmp = ft_split(tab[i], ' ');
		if (ft_strcmp(tmp[0], "<<"))
			tab_trimmer(tmp);
		debug_tab(tmp);
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
//		pipeline_debug(wrp->pipeline); 		
/*  		if (wrp->pipeline->redir)	
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
//	printf ("errnum : %d\n", flag);
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
//	printf ("len : %d\n", len);
//	printf ("{%s}\n", string);
	if (!ft_strncmp(string, "| |", 3))
		return (-2);
	else if (!ft_strncmp(string, "|", 1))
		return (-1);
	else if ((!ft_strncmp(string, "\"", 1) && len < 2) || (!ft_strncmp(string, "\'", 1) && len < 2) || (string[len - 1] == '|' && string[len] == '\0') || *string == 0)
		return (0);
	return (check_line_syntax2(string));
}

int			check_line_syntax2(char *string)
{
	int 	i;

	i = 0;
	while (string[i])
	{
		if ((string[i] == '<' && string[i + 1] == '\0') || (string[i] == '<' && string[i + 1] == '<' && string[i + 2] == '\0'))
			return (-3);
		else if ((string[i] == '<' && string[i + 1] == '<' && string[i + 2] == '<' && string[i + 3] == '\0'))
			return (-3);
		else if ((string[i] == '>' && string[i + 1] == '\0') || (string[i] == '>' && string[i + 1] == '>' && string[i + 2] == '\0'))
			return (-3);
		else if (string[i] == '<' && string[i] == '>')
			return (-3);
		else if ((string[i] == '>' && string[i + 1] == '>' && string[i + 2] == '>' && string[i + 3] == '\0'))
			return (-4);
		else if ((string[i] == '>' && string[i + 1] == '>' && string[i + 2] == '>' && string[i + 3] == '>' && string[i + 4] == '\0'))
			return (-5);
		i++;
	}
	return (1);
}
