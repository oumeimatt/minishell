/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 13:49:24 by ztaouil           #+#    #+#             */
/*   Updated: 2021/09/05 16:39:24 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_line(t_wrapper *wrp, char *line)
{
	if (line == NULL || !(*line))
	{
		put_err(wrp);
		return (0);
	}
	else
	{
		parse_tokens(&(wrp->pipeline), line);
		free (line);
		line = NULL;
		return (1);
	}
}

void	skip_flag(int *flag)
{
	if (*flag >= 1)
		*flag -= 1;
	else if (!(*flag))
		*flag = 0;
}

void	ctrl_d(t_wrapper *wrp, char *line)
{
	if (!line)
	{
		(void)wrp;
		ft_putendl_fd("exit", 2);
		destroy_lenv(wrp->env);
		free (line);
		if (g_vars.i == 1)
			exit (1);
		exit (0);
	}
}

int	is_line(char *line)
{
	if (line && *line)
		add_history(line);
	if (line && !line[0])
	{	
		free (line);
		return (0);
	}
	return (1);
}

char	*reformat_line(t_wrapper *wrp, char *line)
{
	int	flag;

	flag = 0;
	flag = check_line_syntax(line);
	if (flag <= 0)
	{
		load_msg_err(wrp, flag);
		free(line);
		line = NULL;
		return (NULL);
	}
	line = redirection_reformat(line);
	line = pipes_reformat(line);
	line = expand_exit_code(line);
	line = expand_env(wrp, line);
	line = ft_strtrim(line, "\t ");
	return (line);
}
