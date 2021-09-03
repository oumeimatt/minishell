/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:09:56 by oel-yous          #+#    #+#             */
/*   Updated: 2021/09/03 13:23:13 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*ft_filename(char *str)
{
	int		i;

	i = 0;
	while(str[i] == '.')
	{
		if (str[++i] == '/')
			return (str + i + 1);
	}
	return (str);
}

void    exec_cmd(char **cmd, t_list **env, char *error)
{
	char	**arr;
	DIR 	*dirp;
	char	**wrng_cmd;

	arr = list_to_arr(env);
	wrng_cmd = ft_split_2(cmd[0], ' ');
	if (execve(cmd[0], cmd, arr) == -1 && (ft_strncmp(cmd[0], "./", 2) &&
		ft_strncmp(cmd[0], "../", 2)))
	{
		ft_print_error(wrng_cmd[0], error);
		destroy_tab(wrng_cmd, 0);
		destroy_tab(arr, 0);
		exit (127);
	}
	else
	{
		dirp = opendir(ft_filename(wrng_cmd[0]));
		if (!dirp)
			ft_print_error(wrng_cmd[0], PD);
		else
		{
			closedir(dirp);
			ft_print_error(wrng_cmd[0], ID);
		}
		destroy_tab(wrng_cmd, 0);
		destroy_tab(arr, 0);
		exit(126);
	}
}

void	unset_path_cmd(t_wrapper *wrp)
{
	int		stats;

	if (is_builtin(((t_command *)(wrp->pipeline->data))->tokens) == 1)
	{
		g_vars.pid = fork();
		if (g_vars.pid < 0)
			exit(1);
		if (g_vars.pid == 0)
			exec_cmd(((t_command *)(wrp->pipeline->data))->tokens, &wrp->env, NSFD);
		waitpid(g_vars.pid, &stats, 0);
		if (WIFEXITED(stats))
			g_vars.i = WEXITSTATUS(stats);
	}
	else
		exec_builtin(((t_command *)(wrp->pipeline->data))->tokens, &wrp->env, 0);
}

void	ft_only_cmd(t_wrapper *wrp)
{
	int		stats;

	if (is_path_exist(wrp->pipeline, &wrp->env) == TRUE)
	{
		g_vars.pid = fork();
		if (g_vars.pid < 0)
			exit(1);
		if (g_vars.pid == 0)
			exec_cmd(((t_command *)(wrp->pipeline->data))->tokens, &wrp->env, CNF);
		waitpid(g_vars.pid, &stats, 0);
		if (WIFEXITED(stats))
			g_vars.i = WEXITSTATUS(stats);
	}
	else if (is_path_exist(wrp->pipeline, &wrp->env) == 2)
		exec_builtin(((t_command *)(wrp->pipeline->data))->tokens, &wrp->env, 0);
	else if (is_path_exist(wrp->pipeline, &wrp->env) == FALSE)
			unset_path_cmd(wrp);
}
