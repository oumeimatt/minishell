/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 13:38:26 by ztaouil           #+#    #+#             */
/*   Updated: 2021/09/04 13:42:22 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"

void	debug_env(t_list *env)
{
	t_list *temp = env;
	
	if (temp)
	{
		while (temp != NULL)
		{
			printf ("%s || %s\n", ((t_env *)temp->data)->key, ((t_env *)temp->data)->value);
			temp = temp->next;
		}
		printf ("\n\n");
	}
}

void	debug_pipeline(t_list *pipeline)
{
	t_list *temp = pipeline;
	if (temp)
	{
		while (temp->next != NULL)
		{
			debug_tab(((t_command *)(temp->data))->tokens);
			debug_redir(((t_command *)(temp->data))->redir);
			printf (" |");
			temp = temp->next;
		}
		debug_tab(((t_command *)(temp->data))->tokens);
		debug_redir(((t_command *)(temp->data))->redir);
		printf ("\n");		
	}
}

void	debug_redir(t_list *redir)
{
	t_list *temp = redir;
	if (temp)
	{
		while (temp != NULL)
		{
			printf ("\t%d, %s\t", ((t_redir *)(temp->data))->type, ((t_redir *)(temp->data))->filename);
			temp = temp->next;
		}
	}	
}
