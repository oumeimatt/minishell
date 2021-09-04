/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:09:56 by oel-yous          #+#    #+#             */
/*   Updated: 2021/09/04 17:28:45 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*ft_filename(char *str)
{
	int		i;

	i = 0;
	while (str[i] == '.')
	{
		if (str[++i] == '/')
			return (str + i + 1);
	}
	return (str);
}

void	exec_dir(char *cmd)
{
	DIR			*dirp;
	// struct stat	filestat;

	// if (!stat(cmd, &filestat) && filestat.st_mode & S_IXUSR)
	// 	exit(0);
	dirp = opendir(ft_filename(cmd));
	if (!dirp)
		ft_print_error(cmd, PD);
	else
	{
		closedir(dirp);
		ft_print_error(cmd, ID);
	}
}

void	exec_cmd(char **cmd, t_list **env, char *error)
{
	char	**arr;
	char	**wrng_cmd;
	int		excv;

	arr = list_to_arr(env);
	wrng_cmd = ft_split_2(cmd[0], ' ');
	excv = execve(cmd[0], cmd, arr);
	if (excv == -1 && (ft_strncmp(cmd[0], "./", 2)
			&& ft_strncmp(cmd[0], "../", 2)))
	{
		ft_print_error(wrng_cmd[0], error);
		exit (127);
	}
	else
	{
		exec_dir(wrng_cmd[0]);
		exit(126);
	}
	destroy_tab(wrng_cmd, 0);
	destroy_tab(arr, 0);
}

void	unset_path_cmd(t_wrapper *wrp)
{
	int		stats;

	stats = 0;
	if (is_builtin(((t_command *)(wrp->pipeline->data))->tokens) == 1)
	{
		g_vars.pid = fork();
		if (g_vars.pid < 0)
			exit(1);
		if (g_vars.pid == 0)
			exec_cmd(((t_command *)(wrp->pipeline->data))->tokens,
				&wrp->env, NSFD);
		waitpid(g_vars.pid, &stats, 0);
		if (WIFEXITED(stats))
			g_vars.i = WEXITSTATUS(stats);
	}
	else
		exec_builtin(((t_command *)(wrp->pipeline->data))->tokens,
			&wrp->env, 0);
}

void	ft_only_cmd(t_wrapper *wrp)
{
	int		stats;

	stats = 0;
	if (is_path_exist(wrp->pipeline, &wrp->env) == TRUE)
	{
		g_vars.pid = fork();
		if (g_vars.pid < 0)
			exit(1);
		if (g_vars.pid == 0)
			exec_cmd(((t_command *)(wrp->pipeline->data))->tokens,
				&wrp->env, CNF);
		waitpid(g_vars.pid, &stats, 0);
		if (WIFEXITED(stats))
			g_vars.i = WEXITSTATUS(stats);
	}
	else if (is_path_exist(wrp->pipeline, &wrp->env) == 2)
		exec_builtin(((t_command *)(wrp->pipeline->data))->tokens,
			&wrp->env, 0);
	else if (is_path_exist(wrp->pipeline, &wrp->env) == FALSE)
		unset_path_cmd(wrp);
}
