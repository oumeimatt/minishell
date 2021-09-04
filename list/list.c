/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 13:42:44 by ztaouil           #+#    #+#             */
/*   Updated: 2021/09/04 13:43:25 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	*new_list(void *data)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->data = data;
	lst->next = NULL;
	return (lst);
}

t_list	*last_list(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	size_list(t_list *lst)
{
	int	i;

	i = 0;
	while (lst->next)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	addback_list(t_list **alst, t_list *lst)
{
	t_list	*tmp;

	if (!*alst)
		*alst = lst;
	else if (alst && lst && *alst)
	{
		tmp = last_list(*alst);
		tmp->next = lst;
	}
}

void	destroy_list(t_list *lst)
{
	t_list	*next;
	t_list	*current;

	if (!lst)
		return ;
	current = lst;
	while (current != NULL)
	{
		next = current->next;
		free (lst->data);
		free (current);
		current = next;
	}
	lst = NULL;
}
