/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 17:01:19 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/11 17:04:51 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void			put_err(t_wrapper *wrp)
{
    if (wrp->error->num == -1)
        ft_putstr_fd(wrp->error->errmsg, 2);
}

void			load_msg_err(t_wrapper *wrp, int flag)
{
    wrp->error->num = flag;
    if (flag == -1)
        wrp->error->errmsg = ft_strdup("bash: syntax error near unexpected token `|'\n");
}