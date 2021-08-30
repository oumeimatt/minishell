/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 16:13:53 by oel-yous          #+#    #+#             */
/*   Updated: 2021/08/30 14:53:49 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char    *pwd_builtin()
{
	char	*buff;
	int		size;
	char	*str;

	size = 100;
	buff = malloc(sizeof(char) * size);
	str =  getcwd(buff, 100);
	// printf("=======%s======\n", str);
	// free(buff);
	return (str);
}

void	exec_pwd(t_list **env, int x)
{
	char	*pwd;

	pwd = pwd_builtin();
	if (pwd)
	{
		if (ft_strncmp(pwd + ft_strlen(pwd) - 2, "/.", 2))
			ft_putendl_fd(pwd, 1);
	}
	else
	{
		if (ft_strncmp(pwd + ft_strlen(pwd) - 2, "/.", 2))
			change_value(env, "PWD", ft_strjoin(get_value_env(env, "OLDPWD"), "/."));
		else
			change_value(env, "PWD", ft_strjoin(get_value_env(env, "OLDPWD"), "/."));
		ft_putendl_fd(get_value_env(env, "PWD"), 1);
	}
	if (x == 1)
		exit(0);
}
