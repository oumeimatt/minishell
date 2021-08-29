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

#include "builtins.h"

void    exec_env(t_list *env, int x)
{
    t_list *tmp = env;

    while(tmp != NULL)
	{
        if (valid_export(((t_env *)(tmp->data))->value) != 2 && tmp->next != NULL)
            tmp = tmp->next;
        if(tmp->next == NULL)
        {
            if (valid_export(((t_env *)(tmp->data))->value) == 2)
            {
                ft_putendl_fd(((t_env *)(tmp->data))->value, 1);
                break ;
            }
            else
                break ;
        }
        else
        {
            if (valid_export(((t_env *)(tmp->data))->value) == 2)
            {
                ft_putendl_fd(((t_env *)(tmp->data))->value, 1);
                tmp = tmp->next;
            }
            else
                tmp = tmp->next;
        }
    }
	if (x == 1)
		exit(0);
}

int     is_key_exist(t_list *env, char *key)
{
    t_list   *temp;

    temp = env;
    while (temp != NULL)
    {
        if (temp->next == NULL)
        {
            if (ft_strcmp(key, ((t_env *)(temp->data))->key) == 0)
                return (0);
            else
                return (1);
        }
        else
        {
            if (ft_strcmp(key, ((t_env *)(temp->data))->key) == 0)
                return (0);
            temp = temp->next;
        }
    }
    return (1);
}
