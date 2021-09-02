/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 16:31:04 by oel-yous          #+#    #+#             */
/*   Updated: 2021/09/02 19:34:01 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	change_value(t_list **env, char *key, char *value)
{
    t_list   *tmp;

    tmp = *env;
    while (tmp != NULL)
    {
        if (!ft_strcmp(key, ((t_env *)(tmp->data))->key))
        {
            free(((t_env *)(tmp->data))->value);
            ((t_env *)(tmp->data))->value = ft_strdup(value);
        }
		if (tmp->next)
        	tmp = tmp->next;
		else
			break;
    }
}

void    cd_only(t_list **env)
{
	char	*buff;
	char	*oldpwd;
	char	*tmp;

	buff = NULL;
	if (is_key_exist(env, "HOME") == 1)
	{
		ft_putendl_fd("petitshell: cd: HOME not set\n", 2);
		g_vars.i = 1;
	}
	else
	{
		oldpwd = ft_strdup(get_value_env(env, "PWD"));
		change_value(env, "OLDPWD", oldpwd);
		buff = ft_strdup(get_value_env(env, "HOME"));
		chdir(buff);
		tmp = ft_strjoin("=", buff);
		change_value(env, "PWD", buff);
		free_ret(oldpwd, NULL);
		free_ret(buff, NULL);
		free_ret(tmp, NULL);
	}
}

void    exec_cd(char **str, t_list **env, int x)
{
	int     i;
	char	*oldpwd;
	char	*pwd = NULL;
	char	buff[100];

	if (str[1] == NULL)
		cd_only(env);
	else
	{
		oldpwd = ft_strdup(get_value_env(env, "PWD"));
		i = chdir(str[1]);
		if (i == 0)
		{
			change_value(env, "OLDPWD", oldpwd);
			if (getcwd(buff, 100))
				pwd = ft_strjoin("=", getcwd(buff, 100));
			else
				pwd = ft_strdup(get_value_env(env, "PWD"));
			change_value(env, "PWD", pwd);
		}
		else
		{
			ft_putstr_fd("petitshell: cd: ", 2);
			ft_putstr_fd(str[1], 2);
			ft_putendl_fd(": No such file or directory", 2);
			g_vars.i = 1;
		}
		free_ret(pwd, NULL);
		free_ret(oldpwd, NULL);
	}
	if (x == 1)
		exit(0);
}
