/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 13:57:18 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/07 14:58:51 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int			is_redir(char *str)
{
	if (!ft_strcmp(str, "<"))
		return (1);
	else if (!ft_strcmp(str, "<<"))
		return (2);
	else if (!ft_strcmp(str, ">"))
		return (3);
	else if (!ft_strcmp(str, ">>"))
		return (4);
	else
		return (0);
}
