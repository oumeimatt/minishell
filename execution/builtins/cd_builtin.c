/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 16:31:04 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/09 15:47:06 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env   *change_value(t_env *env, char *key, char *value)
{
    t_env   *tmp;
    int     found_key;

    found_key = 0;
    tmp = env;
    while (tmp != NULL)
    {
        if (tmp->next == NULL && found_key == 1)
        {
            if (strcmp(key, tmp->key) == 0)
            {
                free(tmp->value);
                tmp->value = ft_strdup(value);
            }
            else
                break;
        }
        else
        {
            if (strcmp(key, tmp->key) == 0)
            {
                free(tmp->value);
                tmp->value = ft_strdup(value);
                found_key = 1;
            }
            tmp = tmp->next;
        }
    }
    return (env);
}

void    cd_only(char *buff, t_env *env, char *oldpwd)
{
	if (is_key_exist(env, "HOME") == FALSE)
		printf("%minishell: cd: HOME not set\n");
	else
	{
		oldpwd = ft_strjoin("OLDPWD=", pwd_builtin());
		env = change_value(env, "OLDPWD", oldpwd);
		buff = print_value(env, "HOME");
		chdir(buff);
		buff = ft_strjoin("PWD=", buff);
		env = change_value(env, "PWD", buff);
	}
}

void    exec_cd(char **str, t_env *env, int x)
{
	char    *buff;
	int     size;
	int     i;
	char	*oldpwd;
	char	*pwd;

	size = 100;
	oldpwd = NULL;
	buff = malloc(sizeof(char) * size);
	if (str[1] == NULL)
		cd_only(buff, env, oldpwd);
	else
	{
		oldpwd = ft_strjoin("OLDPWD=", pwd_builtin());
		i = chdir(str[1]);
		if (i == 0)
		{
			env = change_value(env, "OLDPWD", oldpwd);
			pwd = pwd_builtin();
			buff = ft_strjoin("PWD=", pwd);
			env = change_value(env, "PWD", buff);
		}
		else
			printf("minishell: %s: %s: %s\n", str[0], str[1],
				strerror(errno));
	}
	free(buff);
	if (x == 1)
		exit(0);
}
