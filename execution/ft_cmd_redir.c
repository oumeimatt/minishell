/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:53:35 by oel-yous          #+#    #+#             */
/*   Updated: 2021/08/30 12:24:12 by oel-yous         ###   ########.fr       */
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
		return (NULL);
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
		return (NULL);
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
	if (!ft_hook_in(redir) && ft_hook_out(redir))
		return (ft_hook_out(redir));
	else if (!ft_hook_out(redir) && ft_hook_in(redir))
		return (ft_hook_in(redir));
	else
		return (NULL);
}

t_list	*ft_hook(t_list *redir)
{
	t_list	*tmp;

	tmp = NULL;
	check_errors(redir);
	if (redir->next != NULL)
	{
		if (!same_redir(redir))
		{
			tmp = new_list((void*)ft_hook_in(redir));
			addback_list(&tmp, new_list((void*)ft_hook_out(redir)));
		}
		else
			tmp = new_list((void *)same_redir(redir));
	}
	else
		tmp = new_list((void *)same_redir(redir));
	return (tmp);
}

void	ft_redir_cmd(t_wrapper *wrp, int i)
{
	char		*path;
	char		**split_path;
	
	path = get_path(&wrp->env);
	((t_command *)wrp->pipeline->data)->redir = 
		ft_hook((((t_command *)(wrp->pipeline->data))->redir));
	if (path != NULL)
	{
		split_path = ft_split_2(path, ':');	
		if (is_builtin(((t_command *)wrp->pipeline->data)->tokens) == 1)
            exec_cmd_redir(wrp, split_path, i);
		else
           	exec_builtin_redir(wrp);
	}
	else
        unset_path_redir(wrp);
}

void    unset_path_redir(t_wrapper *wrp)
{
	int		stats;

	stats = 0;
	((t_command *)wrp->pipeline->data)->redir = 
		ft_hook((((t_command *)(wrp->pipeline->data))->redir));
	if (is_builtin(((t_command *)wrp->pipeline->data)->tokens) == 1)
	{
		g_vars.pid = fork();
		if (g_vars.pid < 0)
			exit(1);
		if (g_vars.pid == 0)
		{
			ft_is_redirection((((t_command *)(wrp->pipeline->data))->redir));
			if (execve(((t_command *)wrp->pipeline->data)->tokens[0],
				((t_command *)wrp->pipeline->data)->tokens, NULL) == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(((t_command *)wrp->pipeline->data)->tokens[0], 2);
				ft_putendl_fd(": No such file or directory", 2);
				exit(127);
			}
		}
		waitpid(g_vars.pid, &stats, 0);
		if (WIFEXITED(stats))
			g_vars.i = WEXITSTATUS(stats);
	}
	else
		ft_unset_path_builtin(wrp, stats);
}

void	ft_unset_path_builtin(t_wrapper *wrp, int stats)
{
	g_vars.pid = fork();
	if (g_vars.pid < 0)
		exit(1);
	if (g_vars.pid == 0)
	{
		ft_is_redirection((((t_command *)(wrp->pipeline->data))->redir));
		exec_builtin(((t_command *)wrp->pipeline->data)->tokens, &wrp->env, 1);
	}
	waitpid(g_vars.pid, &stats, 0);
	if (WIFEXITED(stats))
		g_vars.i = WEXITSTATUS(stats);
}

void    exec_cmd_redir(t_wrapper *wrp, char **split_path, int i)
{
	int		stats;

    ((t_command *)wrp->pipeline->data)->tokens[0] = 
		absolute_path(((t_command *)wrp->pipeline->data)->tokens[0], split_path);
	if (i == 0)
	{
		g_vars.pid = fork();
		if (g_vars.pid  < 0)
			exit(1);
		if (g_vars.pid  == 0)
		{
			ft_is_redirection((((t_command *)(wrp->pipeline->data))->redir));
			exec_cmd(((t_command *)wrp->pipeline->data)->tokens, wrp);
		}
		waitpid(g_vars.pid , &stats, 0);
		if (WIFEXITED(stats))
			g_vars.i = WEXITSTATUS(stats);
	}
	else
		exec_cmd(((t_command *)wrp->pipeline->data)->tokens, wrp);
}

void    exec_builtin_redir(t_wrapper *wrp)
{
	int		stats;

	g_vars.pid  = fork();
	if (g_vars.pid  < 0)
		exit(1);
	if (g_vars.pid  == 0)
	{
		ft_is_redirection((((t_command *)(wrp->pipeline->data))->redir));
		exec_builtin(((t_command *)wrp->pipeline->data)->tokens, &wrp->env, 1);
	}
	waitpid(g_vars.pid , &stats, 0);
	if (WIFEXITED(stats))
		g_vars.i = WEXITSTATUS(stats);
}
