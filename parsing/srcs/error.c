/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 17:01:19 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/14 17:57:27 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void			put_err(t_wrapper *wrp)
{
	if (wrp->error->errnum <= -1)
		ft_putstr_fd(wrp->error->errmsg, 2);
	fill_exit_code(wrp);
}

void			load_msg_err(t_wrapper *wrp, int flag)
{
	wrp->error->errnum = flag;
	if (flag == -1)
		wrp->error->errmsg = ft_strdup("minishell: syntax error near unexpected token `|'\n");
	else if (flag == -2)
		wrp->error->errmsg = ft_strdup("minishell: syntax error near unexpected token `||'\n");
	else if (flag == -3)
		wrp->error->errmsg = ft_strdup("minishell: syntax error near unexpected token `newline'\n");
	else if (flag == -4)
		wrp->error->errmsg = ft_strdup("minishell: syntax error near unexpected token `>'\n");
	else if (flag == -5)
		wrp->error->errmsg = ft_strdup("minishell: syntax error near unexpected token `>>'\n");
	else if (flag == -6)
		wrp->error->errmsg = ft_strdup("minishell: syntax error near unexpected token `<'\n");
	else if (flag == -7)
		wrp->error->errmsg = ft_strdup("minishell: syntax error near unexpected token `<<'\n");

}

void            fill_exit_code(t_wrapper *wrp)
{
	if (wrp->error->errnum >= -7 && wrp->error->errnum <= -1)
	{
		g_variables.i = 258;
	}
}