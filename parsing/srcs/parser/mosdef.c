/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mosdef.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 11:01:42 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/05 21:45:47 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int				GetTabSize(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}



t_pipeline		*pipeline_last(t_pipeline *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_pipeline		*pipeline_new(t_cmd cmd)
{
	t_pipeline	*lst;

	if (!(lst = malloc(sizeof(t_pipeline))))
		return (NULL);
	lst->cmd = cmd;
	lst->next = NULL;
	return (lst);
}

int				pipeline_size(t_pipeline *lst)
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
void			pipeline_addback(t_pipeline **alst, t_pipeline *lst)
{
	t_pipeline	*tmp;
	
	if (!*alst)
		*alst = lst;
	else if (alst && lst && *alst)
	{
		tmp = pipeline_last(*alst);
		tmp->next = lst;
	}
}

t_wrapper		*contruct_wrapper(void)
{
	t_wrapper *wrp;

	if (!(wrp = (t_wrapper *)malloc(sizeof(t_wrapper))))
		return (NULL);
	return (wrp);
}

void			pipeline_debug(t_pipeline *lst)
{
	if (lst)
	{	
		while (lst->next)
		{
			for (int i = 0; (lst->cmd.tokens)[i]; i++)
				printf ("[%s]", (lst->cmd.tokens)[i]);
			printf (" | ");
			lst = lst->next;	
		}
		for (int i = 0; (lst->cmd.tokens)[i]; i++)
			printf ("[%s]", (lst->cmd.tokens)[i]);
		printf ("\n");
	}
}