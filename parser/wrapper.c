/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 13:44:03 by ztaouil           #+#    #+#             */
/*   Updated: 2021/09/04 13:44:10 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	destroy_wrapper(t_wrapper *wrp)
{
	destroy_lenv(wrp->env);
	destroy_lcommand(wrp->pipeline);
}
