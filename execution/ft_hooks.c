/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 10:29:48 by oel-yous          #+#    #+#             */
/*   Updated: 2021/09/04 10:47:28 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_redir	*hooks_helper(int type, char *filename)
{
	if (type != 0)
		return (new_redir(type, filename));
	else
	{
		free(filename);
		return (NULL);
	}
}

t_redir	*ft_hook_in(t_list *redir)
{
	t_list		*tmp;
	int			type;
	char		*filename;

	tmp = redir;
	type = 0;
	filename = ft_strdup("");
	while (tmp != NULL)
	{
		if (((t_redir *)tmp->data)->type == 1)
		{
			free(filename);
			type = ((t_redir *)tmp->data)->type;
			filename = ft_strdup(((t_redir *)tmp->data)->filename);
		}
		if (tmp->next != NULL)
			tmp = tmp->next;
		else
			break ;
	}
	return (hooks_helper(type, filename));
}

t_redir	*ft_hook_out(t_list *redir)
{
	t_list		*tmp;
	int			type;
	char		*filename;	

	tmp = redir;
	type = 0;
	filename = ft_strdup("");
	while (tmp != NULL)
	{
		if (((t_redir *)tmp->data)->type == 3
			|| ((t_redir *)tmp->data)->type == 4)
		{
			free(filename);
			type = ((t_redir *)tmp->data)->type;
			filename = ft_strdup(((t_redir *)tmp->data)->filename);
		}
		if (tmp->next != NULL)
			tmp = tmp->next;
		else
			break ;
	}
	return (hooks_helper(type, filename));
}

t_redir	*same_redir(t_list *redir)
{
	t_redir		*in;
	t_redir		*out;

	in = ft_hook_in(redir);
	out = ft_hook_out(redir);
	if (!in && out)
		return (out);
	else if (!out && in)
		return (in);
	else
	{
		destroy_redir(in);
		destroy_redir(out);
		return (NULL);
	}
}

t_list	*ft_hook(t_list *redir)
{
	t_list	*redirlist;
	t_redir	*tmp;
	t_redir	*tmp2;

	redirlist = NULL;
	tmp = same_redir(redir);
	tmp2 = NULL;
	if (redir->next != NULL)
	{
		if (!tmp)
		{
			tmp = ft_hook_in(redir);
			redirlist = new_list((void *)tmp);
			tmp2 = ft_hook_out(redir);
			addback_list(&redirlist, new_list((void *)tmp2));
		}
		else
			redirlist = new_list((void *)tmp);
	}
	else
		redirlist = new_list((void *)tmp);
	destroy_lredir(redir);
	return (redirlist);
}
