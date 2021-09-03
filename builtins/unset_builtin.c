/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 16:29:06 by oel-yous          #+#    #+#             */
/*   Updated: 2021/09/03 14:14:09 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void    unset_error(char *str)
{
	ft_putstr_fd("petitshell: unset: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_vars.i = 1;
}

void    exec_unset(char **str, t_list **env, int x)
{
	int     i;

	i = 1;
	if (str[i] == NULL)
		return ;
	while (str[i] != NULL)
	{
		if (valid_export(str[i]) == 1)
			unset_error(str[i]);
		else
			delete_node_env(env, str[i]);
		i++;
	}
	if (x == 1)
		exit(0);
}
