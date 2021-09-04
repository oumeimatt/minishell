/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 09:17:14 by ztaouil           #+#    #+#             */
/*   Updated: 2021/09/04 13:50:59 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

int	is_dollar(char c)
{
	if (c == '$')
		return (1);
	return (0);
}

int	is_squote(char c)
{
	if (c == 39)
		return (1);
	return (0);
}

int	is_dquote(char c)
{
	if (c == '"')
		return (1);
	return (0);
}
