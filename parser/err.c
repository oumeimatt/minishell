/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 14:29:45 by ztaouil           #+#    #+#             */
/*   Updated: 2021/09/04 16:40:29 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	put_err(t_wrapper *wrp)
{
	if (wrp->error.errnum <= -1)
		if(wrp->error.errmsg)
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
