/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:53:35 by oel-yous          #+#    #+#             */
/*   Updated: 2021/09/03 13:25:32 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_redir		*ft_hook_in(t_list *redir)
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
			break;
	}
	if (type != 0)
		return (new_redir(type, filename));
	else
	{
		free(filename);
		return (NULL);
	}
}

t_redir		*ft_hook_out(t_list *redir)
{
	t_list		*tmp;
	int			type;
	char		*filename;	

	tmp = redir;
	type = 0;
	filename = ft_strdup("");
	while (tmp != NULL)
	{
		if (((t_redir *)tmp->data)->type== 3)
		{
			free(filename);
			type = ((t_redir *)tmp->data)->type;
			filename = ft_strdup(((t_redir *)tmp->data)->filename);
		}
		else if (((t_redir *)tmp->data)->type == 4)
		{
			free(filename);
			type = ((t_redir *)tmp->data)->type;
			filename = ft_strdup(((t_redir *)tmp->data)->filename);
		}
		if (tmp->next != NULL)
			tmp = tmp->next;
		else
			break;
	}
	if (type != 0)
		return (new_redir(type, filename));
	else
	{
		free(filename);
		return (NULL);
	}
}

void	check_errors(t_list *redir)
{
	t_list *tmp;

	tmp = redir;
	while (tmp != NULL)
	{
		if (((t_redir *)tmp->data)->type == 1 && g_vars.i != 123)
			ft_in_redir(tmp);
		else if (((t_redir *)tmp->data)->type == 3 && g_vars.i != 123)
			ft_out_redir(tmp);
		else if (((t_redir *)tmp->data)->type == 4 && g_vars.i != 123)
			ft_append_redir(tmp);
		if (tmp->next != NULL)
			tmp = tmp->next;
		else
			break;
	}
}

t_redir		*same_redir(t_list *redir)
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
	t_redir *tmp2;

	redirlist = NULL;
	tmp = same_redir(redir);
	tmp2 = NULL;
	if (redir->next != NULL)
	{
		if (!tmp)
		{
			tmp = ft_hook_in(redir);
			redirlist = new_list((void*)tmp);
			tmp2 = ft_hook_out(redir);
			addback_list(&redirlist, new_list((void*)tmp2));
		}
		else
			redirlist = new_list((void *)tmp);
	}
	else
		redirlist = new_list((void *)tmp);
	 destroy_lredir(redir);
	return (redirlist);

}

void	ft_redir_cmd(t_wrapper *wrp)
{
	check_errors(((t_command *)wrp->pipeline->data)->redir);
	((t_command *)wrp->pipeline->data)->redir = 
		ft_hook((((t_command *)(wrp->pipeline->data))->redir));
	if (is_path_exist(wrp->pipeline, &wrp->env) == TRUE) // NOT BUILTIN
        exec_cmd_redir(wrp);
	else if (is_path_exist(wrp->pipeline, &wrp->env) == 2)
        exec_builtin_redir(wrp);
	else if (is_path_exist(wrp->pipeline, &wrp->env) == 3)
			ft_is_redirection((((t_command *)(wrp->pipeline->data))->redir), 0);
	else
        unset_path_redir(wrp);
}

void    unset_path_redir(t_wrapper *wrp)
{
	int		stats;

	stats = 0;
	if (is_builtin(((t_command *)wrp->pipeline->data)->tokens) == 1)
	{
		g_vars.pid = fork();
		if (g_vars.pid < 0)
			exit(1);
		if (g_vars.pid == 0)
		{
			ft_is_redirection((((t_command *)(wrp->pipeline->data))->redir), 1);
			exec_cmd(((t_command *)wrp->pipeline->data)->tokens, &wrp->env, NSFD);
		}
		waitpid(g_vars.pid, &stats, 0);
		if (WIFEXITED(stats))
			g_vars.i = WEXITSTATUS(stats);
	}
	else if (is_builtin(((t_command *)wrp->pipeline->data)->tokens) == 0)
		ft_unset_path_builtin(wrp, stats);
	else
		ft_is_redirection((((t_command *)(wrp->pipeline->data))->redir), 0);
}

void	ft_unset_path_builtin(t_wrapper *wrp, int stats)
{
	g_vars.pid = fork();
	if (g_vars.pid < 0)
		exit(1);
	if (g_vars.pid == 0)
	{
		ft_is_redirection((((t_command *)(wrp->pipeline->data))->redir), 1);
		exec_builtin(((t_command *)wrp->pipeline->data)->tokens, &wrp->env, 1);
	}
	waitpid(g_vars.pid, &stats, 0);
	if (WIFEXITED(stats))
		g_vars.i = WEXITSTATUS(stats);
}

void    exec_cmd_redir(t_wrapper *wrp)
{
	int		stats;

	g_vars.pid = fork();
	if (g_vars.pid  < 0)
		exit(1);
	if (g_vars.pid  == 0)
	{
		ft_is_redirection((((t_command *)(wrp->pipeline->data))->redir), 1);
		exec_cmd(((t_command *)wrp->pipeline->data)->tokens, &wrp->env, CNF);
	}
	waitpid(g_vars.pid , &stats, 0);
	if (WIFEXITED(stats))
		g_vars.i = WEXITSTATUS(stats);
}

void    exec_builtin_redir(t_wrapper *wrp)
{
	int		stats;

	g_vars.pid  = fork();
	if (g_vars.pid  < 0)
		exit(1);
	if (g_vars.pid  == 0)
	{
		ft_is_redirection((((t_command *)(wrp->pipeline->data))->redir), 1);
		exec_builtin(((t_command *)wrp->pipeline->data)->tokens, &wrp->env, 1);
	}
	waitpid(g_vars.pid , &stats, 0);
	if (WIFEXITED(stats))
		g_vars.i = WEXITSTATUS(stats);
}
