/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 16:13:53 by oel-yous          #+#    #+#             */
/*   Updated: 2021/08/30 17:03:13 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char    *pwd_builtin(t_list **env)
{
	char	*buff;
	int		size;
	char	*str;

	size = 100;
	buff = malloc(sizeof(char) * size);
	if (is_key_exist(env, "PWD") == 1)
		str = getcwd(buff, 100);
	else
	{
		buff = getcwd(buff, 100);
		if (!buff)
			return (NULL);
		str = get_value_env(env, "PWD") + 4;
	}
	// free(buff);
	return (str);
}

void	exec_pwd(t_list **env, int x)
{
	char	*pwd;

	pwd = pwd_builtin(env);
	if (pwd)
	{
		if (ft_strncmp(pwd + ft_strlen(pwd) - 2, "/.", 2))
			ft_putendl_fd(pwd, 1);
		else
		{
			change_value(env, "OLDPWD", ft_strjoin("OLDPWD=", pwd));
			pwd = ft_strjoin(get_value_env(env, "OLDPWD") + 6, "/.");
			change_value(env, "PWD", ft_strjoin("PWD", pwd));
			ft_putendl_fd(get_value_env(env, "PWD"), 1);
		}
			
	}
	else
	{
		pwd = ft_strjoin(get_value_env(env, "OLDPWD"), "/.");
		change_value(env, "PWD", pwd + 6);
		ft_putendl_fd(get_value_env(env, "PWD"), 1);
	}
	if (x == 1)
		exit(0);
}
