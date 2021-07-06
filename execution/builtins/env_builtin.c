/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 12:42:08 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/06 12:37:16 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing/inc/minishell.h"

void    exec_env(t_env *env)
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
                printf("%s\n", tmp->value);
                return ;
            }
            else
                return ;
        }
        else
        {
            if (valid_export(tmp->value) == 2)
            {
                printf("%s\n", tmp->value);
                tmp = tmp->next;
            }
            else
                tmp = tmp->next;
        }
    }
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
