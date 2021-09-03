/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 16:13:53 by oel-yous          #+#    #+#             */
/*   Updated: 2021/09/03 11:13:57 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char    *pwd_builtin(t_list **env)
{
	char	buff[100];

	if (is_key_exist(env, "PWD") == 1)
		return(getcwd(buff, 100));
	else
		return (ft_strdup(get_value_env(env, "PWD") + 1));
}

void	exec_pwd(t_list **env, int x)
{
	char	*pwd;

	pwd = pwd_builtin(env);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	pwd = NULL;
	if (x == 1)
		exit(0);
}
