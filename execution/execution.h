/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 12:10:04 by oel-yous          #+#    #+#             */
/*   Updated: 2021/09/04 18:07:38 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../parser/parser.h"
# include "../libft/libft.h"
# include "../builtins/builtins.h"
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define NSFD "No such file or directory"
# define PD "Permission denied"
# define ID "is a directory"
# define CNF "command not found"

t_vars	g_vars;

void	ft_print_error(char *cmd, char *error);
int		is_path_exist(t_list *pipeline, t_list **env);
void	execute(t_wrapper *wrp);

void	ft_redir_cmd(t_wrapper *wrp);
void	unset_path_redir(t_wrapper *wrp);
void	ft_unset_path_builtin(t_wrapper *wrp, int stats);
void	exec_cmd_redir(t_wrapper *wrp);
void	exec_builtin_redir(t_wrapper *wrp);

char	*ft_filename(char *str);
void	exec_dir(char *cmd);
void	exec_cmd(char **cmd, t_list **env, char *error);
void	unset_path_cmd(t_wrapper *wrp);
void	ft_only_cmd(t_wrapper *wrp);

int		check_for_heredoc(t_wrapper *wrp);
void	ft_here_doc(t_wrapper *wrp, char *filename, t_list *redir);
void	open_hd_helper(t_list *redir, char *filename, t_wrapper *wrp);
void	ft_open_heredoc(t_wrapper *wrp);
char	*ft_random_name(char *filename);

t_redir	*hooks_helper(int type, char *filename);
t_redir	*ft_hook_in(t_list *redir);
t_redir	*ft_hook_out(t_list *redir);
t_redir	*same_redir(t_list *redir);
t_list	*ft_hook(t_list *redir);

void	ft_pipe_cmd_only(t_list *pipeline, t_list **env);
void	only_cmd_pipe(t_list *pipeline, t_list **env);
void	ft_pipe(t_list *pipeline);
void	ft_pipes_loop(t_wrapper *wrp);

void	ft_pipe_cmd_redir(t_list *pipeline, t_list **env);
void	ft_exec_pipe_redir(t_list *pipeline, t_list **env);
void	ft_exec_pipe_redir_2(t_list *pipeline, t_list **env);

void	ft_append_redir(t_list *redir);
void	ft_out_redir(t_list *redir);
void	ft_in_redir(t_list *redir);
void	check_errors(t_list *redir);

void	ft_dup_out_redir(t_list *redir, int file, int i);
void	ft_is_redirection(t_list *redir, int i);

int		check_first(char **s_path, char *cmd, char **commande);
char	*abs_path(int acc, char **s_path, char *commande, char *failed);
char	*absolute_path(char *cmd, char **s_path);
char	*ft_cmd_path(char *cmd, char *full_path);

#endif