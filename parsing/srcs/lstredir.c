/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstredir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 15:41:48 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/10 19:38:52 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_lstredir		*lstredir_last(t_lstredir *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);	
}

t_lstredir		*lstredir_new(int type, char *filename)
{
	t_lstredir	*lst;

	if (!(lst = malloc (sizeof(t_lstredir))))
		return (NULL);
	lst->type = type;
	lst->filename = filename;
	lst->next = NULL;
	return (lst);
}

int				lstredir_size(t_lstredir *lst)
{
	size_t	i;

	i = 0;
	while (lst->next)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void			lstredir_addback(t_lstredir **alst, t_lstredir *lst)
{
	t_lstredir	*tmp;

	if (!*alst)
	{
		*alst = lst;
	}
	else if (alst && lst && *alst)
	{
		tmp = lstredir_last(*alst);
		tmp->next = lst;
	}
}

void			lstredir_debug(t_lstredir *lst)
{
	if (lst)
	{
		while (lst->next)
		{
			printf ("type : [%d], file : %s\n", lst->type, lst->filename);
			lst = lst->next;
		}
		printf ("type : [%d], file : %s\n", lst->type, lst->filename);
		printf ("\n");
	}
}