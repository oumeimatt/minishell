/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:02:40 by oel-yous          #+#    #+#             */
/*   Updated: 2021/09/03 15:31:31 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	export_error(char *str)
{
	ft_putstr_fd("petitshell: export: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_vars.i = 1;
}

void	exec_export(char **str, t_list **env, int x)
{
	int		i;

	if (str[1] != NULL)
	{
		i = 1;
		while (str[i] != NULL)
		{
			if (valid_export(str[i]) == 1)
				export_error(str[i]);
			else
				export_builtin(str, env, i);
			i++;
		}
		if (x == 1)
			exit(0);
	}
	else
	{
		only_export(env);
		if (x == 1)
			exit(0);
	}
}
