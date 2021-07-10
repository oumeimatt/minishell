/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 18:22:07 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/10 20:24:52 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_add_node(t_env **head_ref, char *line, char *key)
{
    t_env	*new_node;
    t_env	*last;

    new_node = (t_env*) malloc(sizeof(t_env));
    last = *head_ref;
    new_node->value = ft_strdup(line);
    new_node->key = ft_strdup(key);
    new_node->next = NULL;
    if (*head_ref == NULL)
    {
       *head_ref = new_node;
       return;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
    return;
}

void	delete_node(t_env **head_ref, char *key)
{
	t_env *temp;
	t_env *prev;

	temp = *head_ref;
    if (temp != NULL && strcmp(temp->key, key) == TRUE) 
	{
        *head_ref = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && strcmp(temp->key, key) != TRUE)
	{
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return;
    prev->next = temp->next;
    free(temp);
}

void    print_list(t_env *head)
{
    t_env *tmp;
    
    tmp = head;
    while(tmp != NULL)
	{
        if(tmp->next == NULL)
            printf("%s\n", tmp->value);
        else
            printf("%s\n", tmp->value);
        tmp = tmp->next;
    }
}

char    *print_value(t_env *env, char *key)
{
    t_env   *temp;

    temp = env;
    while (temp != NULL)
    {
        if (temp->next == NULL)
        {
            if (ft_strcmp(key, temp->key) == 0)
                return (temp->value + strlen(key) + 1);
            else
                return (NULL);
        }
        else
        {
            if (ft_strcmp(key, temp->key) == 0)
                return (temp->value + strlen(key) + 1);
            temp = temp->next;
        }
    }
    return (NULL);
}
