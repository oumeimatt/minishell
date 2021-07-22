/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 12:42:08 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/09 17:21:47 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    exec_env(t_env *env, int x)
{
    t_env *tmp = env;

    while(tmp != NULL)
	{
        if (valid_export(tmp->value) != 2 && tmp->next != NULL)
            tmp = tmp->next;
        if(tmp->next == NULL)
        {
            if (valid_export(tmp->value) == 2)
            {
                ft_putendl_fd(tmp->value, 1);
                break ;
            }
            else
                break ;
        }
        else
        {
            if (valid_export(tmp->value) == 2)
            {
                ft_putendl_fd(tmp->value, 1);
                tmp = tmp->next;
            }
            else
                tmp = tmp->next;
        }
    }
	if (x == 1)
		exit(0);
}

int     is_key_exist(t_env *env, char *key)
{
    t_env   *temp;

    temp = env;
    while (temp != NULL)
    {
        if (temp->next == NULL)
        {
            if (ft_strcmp(key, temp->key) == 0)
                return (TRUE);
            else
                return (FALSE);
        }
        else
        {
            if (ft_strcmp(key, temp->key) == 0)
                return (TRUE);
            temp = temp->next;
        }
    }
    return (FALSE);
}

t_env	*init_env(char **envp, t_env *list)
{
	int     i;
    int     k;
	char	*line;
    char    *key;

	i = 0;
	while (envp[i] != NULL)
	{
		line = envp[i];
        k = 0;
        key = ft_strdup("");
        while (line[k] != '=' && line[k] != '\0')
            key = ft_charjoin(key, line[k++]);
		ft_add_node(&list, line, key);
        free(key);
		i++;
	}
	return (list);
}
