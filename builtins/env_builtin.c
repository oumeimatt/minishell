/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 12:42:08 by oel-yous          #+#    #+#             */
/*   Updated: 2021/09/02 11:40:36 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void    exec_env(t_list **env, int x)
{
    t_list *tmp;

    tmp = *env;
    while(tmp != NULL)
	{
        if (((t_env *)(tmp->data))->value != NULL)
        {
            ft_putstr_fd(((t_env *)(tmp->data))->key, 1);
            ft_putendl_fd(((t_env *)(tmp->data))->value, 1);
        }
        if (tmp->next || (((t_env *)(tmp->data))->value == NULL && tmp->next))
            tmp = tmp->next;
        else if (!tmp->next)
            break ;
    }
	if (x == 1)
		exit(0);
}

int     is_key_exist(t_list **env, char *key)
{
    t_list   *temp;

    temp = *env;
    while (temp != NULL)
    {
        if (!ft_strcmp(key, ((t_env *)(temp->data))->key))
            return (0);
        if (temp->next)
            temp = temp->next;
        else
            break ; 
    }
    return (1);
}
