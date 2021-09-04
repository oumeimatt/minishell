/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 14:29:45 by ztaouil           #+#    #+#             */
/*   Updated: 2021/09/04 15:58:18 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	put_err(t_wrapper *wrp)
{
	if (wrp->error.errnum <= -1)
		ft_putstr_fd(wrp->error.errmsg, 2);
	fill_exit_code(wrp);
	free (wrp->error.errmsg);
}

void	load_msg_err(t_wrapper *wrp, int flag)
{
	char	*msg;

	printf ("flag : %d\n", flag);
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
	free (msg);
}

void	fill_exit_code(t_wrapper *wrp)
{
	if (wrp->error.errnum >= -7 && wrp->error.errnum <= -1)
	{
		g_vars.i = 258;
	}
}
