/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 16:31:04 by oel-yous          #+#    #+#             */
/*   Updated: 2021/08/30 14:25:48 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	change_value(t_list **env, char *key, char *value)
{
    t_list   *tmp;
    int     found_key;

    found_key = 0;
    tmp = *env;
    while (tmp != NULL)
    {
        if (tmp->next == NULL && found_key == 1)
        {
            if (ft_strcmp(key, ((t_env *)(tmp->data))->key) == 0)
            {
                free(((t_env *)(tmp->data))->value);
                ((t_env *)(tmp->data))->value = ft_strdup(value);
            }
            else
                break;
        }
        else
        {
            if (ft_strcmp(key, ((t_env *)(tmp->data))->key) == 0)
            {
                free(((t_env *)(tmp->data))->value);
                ((t_env *)(tmp->data))->value = ft_strdup(value);
                found_key = 1;
            }
            tmp = tmp->next;
        }
    }
}

void    cd_only(char *buff, t_list **env, char *oldpwd)
{
	if (is_key_exist(env, "HOME") == 1)
	{
		ft_putendl_fd("petitshell: cd: HOME not set\n", 2);
		g_vars.i = 1;
	}
	else
	{
		oldpwd = ft_strjoin("OLDPWD=", pwd_builtin());
		change_value(env, "OLDPWD", oldpwd);
		buff = get_value_env(env, "HOME");
		chdir(buff);
		buff = ft_strjoin("PWD=", buff);
		change_value(env, "PWD", buff);
	}
}

void    exec_cd(char **str, t_list **env, int x)
{
	char    *buff;
	int     size;
	int     i;
	char	*oldpwd;
	char	*pwd;

	size = 100;
	oldpwd = ft_strdup(get_value_env(env, "OLDPWD"));
	pwd = ft_strdup(get_value_env(env, "PWD"));
	buff = malloc(sizeof(char) * size);
	if (str[1] == NULL)
		cd_only(buff, env, oldpwd);
	else
	{
		if (pwd_builtin())
			oldpwd = ft_strjoin("OLDPWD=", pwd_builtin());
		i = chdir(str[1]);
		if (i == 0)
		{
			change_value(env, "OLDPWD", oldpwd);
			if (pwd_builtin())
				pwd = pwd_builtin();
			buff = ft_strjoin("PWD=", pwd);
			change_value(env, "PWD", buff);
			printf("=== PWD %s =====\n", buff);
			printf("=== OLDPWD %s =====\n", oldpwd);
		}
		else
		{
			ft_putstr_fd("petitshell: cd: ", 2);
			ft_putstr_fd(str[1], 2);
			ft_putendl_fd(": No such file or directory", 2);
			g_vars.i = 1;
		}
	}
	if (buff)
		free(buff);
	if (x == 1)
		exit(0);
}
