/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mosdef.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 11:01:42 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/11 16:48:33 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_pipeline		*pipeline_last(t_pipeline *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_pipeline		*pipeline_new(t_cmd cmd, t_lstredir *redir)
{
	t_pipeline	*lst;

	if (!(lst = malloc(sizeof(t_pipeline))))
		return (NULL);
	lst->redir = redir;
	lst->cmd = cmd;
	lst->in = 0;
	lst->out = 1;
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
	{	
		*alst = lst;
	}
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
	if (lst && lst->cmd.tokens)
	{	
		while (lst->next)
		{
			for (int i = 0; lst->cmd.tokens[i] != NULL; i++)
				printf ("[%s]", (lst->cmd.tokens)[i]);
			printf (" | ");
			lst = lst->next;	
		}
		for (int i = 0; (lst->cmd.tokens)[i]; i++)
			printf ("[%s]", (lst->cmd.tokens)[i]);
		printf ("\n");
	}
}