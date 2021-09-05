/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 14:29:45 by ztaouil           #+#    #+#             */
/*   Updated: 2021/09/04 18:46:40 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	put_err(t_wrapper *wrp)
{
	if (wrp->error.errnum <= -1)
		if (wrp->error.errmsg)
			ft_putstr_fd(wrp->error.errmsg, 2);
	fill_exit_code(wrp);
	if (wrp->error.errmsg)
	{
		free (wrp->error.errmsg);
		wrp->error.errmsg = NULL;
	}
}

void	load_msg_err(t_wrapper *wrp, int flag)
{
	char	*msg;

	msg = ft_strdup ("minishell: syntax error near unexpected token");
	wrp->error.errnum = flag;
	if (flag == -1)
		wrp->error.errmsg = ft_strjoin(msg, " `|'\n");
	else if (flag == -2)
		wrp->error.errmsg = ft_strjoin(msg, " `||'\n");
	else if (flag == -3)
		wrp->error.errmsg = ft_strjoin(msg, " `newline'\n");
	else if (flag == -4)
		wrp->error.errmsg = ft_strjoin(msg, " `>'\n");
	else if (flag == -5)
		wrp->error.errmsg = ft_strjoin(msg, " `>>'\n");
	else if (flag == -6)
		wrp->error.errmsg = ft_strjoin(msg, " `<'\n");
	else if (flag == -7)
		wrp->error.errmsg = ft_strjoin(msg, " `<<'\n");
	else if (flag == 0)
		wrp->error.errmsg = ft_strdup("");
	else if (flag == -10)
		wrp->error.errmsg = ft_strdup("Syntax Error\n");
	free (msg);
}

void	fill_exit_code(t_wrapper *wrp)
{
	if (wrp->error.errnum >= -7 && wrp->error.errnum <= -1)
	{
		g_vars.i = 258;
	}
}

int	ext_env_exp(t_venv venv, char *string)
{
	if (is_dollar(string[venv.s_count])
		&& !dollar_valid(string[venv.s_count + 1])
		&& venv.sq[venv.s_count] == 0)
		return (1);
	return (0);
}
