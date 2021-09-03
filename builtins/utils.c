/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:44:18 by oel-yous          #+#    #+#             */
/*   Updated: 2021/09/03 15:44:21 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	find_length(t_list *head)
{
	t_list	*current;
	int		count;

	current = head;
	count = 0;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	**list_to_arr(t_list **head)
{
	int		len;
	char	**arr;
	int		index;
	t_list	*curr;

	len = find_length(*head);
	arr = NULL;
	arr = malloc(sizeof (char **) * (len + 1));
	index = 0;
	curr = *head;
	while (curr != NULL)
	{
		arr[index++] = ft_strdup(((t_env *)(curr->data))->value);
		curr = curr->next;
	}
	arr[len] = NULL;
	return (arr);
}
