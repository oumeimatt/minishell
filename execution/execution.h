#ifndef EXECUTION_H
# define EXECUTION_H

# include "../parser/parser.h"
# include "../libft/libft.h"
# include "../builtins/builtins.h"
# include <dirent.h>
# include <sys/types.h>
# include <fcntl.h>  

# define NSFD "No such file or directory"
# define PD "Permission denied"
# define ID "is a directory"
# define CNF "command not found"

t_vars	g_vars;

void    exec_cmd(char **cmd, t_wrapper *wrp, char *error);
void	unset_path_cmd(t_wrapper *wrp);
void	ft_only_cmd(t_wrapper *wrp);

char	*get_path(t_list **env);
char	*absolute_path(char *cmd, char **s_path);
int	check_first(char **s_path, char *cmd);
char	*ft_cmd_path(char *cmd, char *full_path);
// char	*free_ret(char *str1, char *str2, char *to_ret);


t_redir		*ft_hook_in(t_list *redir);
t_redir		*ft_hook_out(t_list *redir);
t_list	*ft_hook(t_list *redir);
void	ft_redir_cmd(t_wrapper *wrp);
void    unset_path_redir(t_wrapper *wrp);
void	ft_unset_path_builtin(t_wrapper *wrp, int stats);
void    exec_cmd_redir(t_wrapper *wrp);
void    exec_builtin_redir(t_wrapper *wrp);


void	ft_dup_out_redir(t_list *redir, int file, int i);
void	ft_is_redirection(t_list *redir, int i);
void	ft_in_redir(t_list *redir);
void	ft_out_redir(t_list *redir);
void	ft_append_redir(t_list *redir);
void	execute(t_wrapper *wrp);

int		check_for_heredoc(t_wrapper *wrp);
void	ft_here_doc(t_wrapper *wrp, char *filename, t_list *redir);
void	ft_open_heredoc(t_wrapper *wrp);
char	*ft_random_name(char *filename);

void	ft_pipe_cmd_only(t_wrapper *wrp);
void	ft_pipe_cmd_redir(t_wrapper *wrp);
void	ft_exec_pipe_redir(t_wrapper *wrp);
void	ft_exec_pipe_redir_2(t_wrapper *wrp);
void	ft_pipe(t_wrapper *wrp);
void	ft_pipes_loop(t_wrapper *wrp);
void	check_errors(t_list *redir);
char	*free_ret(char *str, char *to_ret);



int		is_path_exist(t_wrapper *wrp);
void	ft_print_error(char **wrng_cmd, char *error);
void	only_cmd_pipe(t_wrapper *wrp);

#endif