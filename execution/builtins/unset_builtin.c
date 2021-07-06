/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 16:29:06 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/06 12:37:34 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing/inc/minishell.h"

void    unset_error(char *str)
{
	ft_putstr_fd("minish: unset: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void    exec_unset(char **str, t_env *env)
{
	int     i;

	i = 1;
	if (str[i] == NULL)
		return ;
	while (str[i] != NULL)
	{
		if (valid_export(str[i]) == FALSE)
		{
			unset_error(str[i]);
			i++;
		}
		else
			delete_node(&env, str[i]);
		i++;
	}
}
