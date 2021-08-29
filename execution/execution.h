#ifndef EXECUTION_H
# define EXECUTION_H

# include "../parser/parser.h"
# include "../libft/libft.h"
# include "../builtins/builtins.h"
# include <fcntl.h>  

void    exec_cmd(char **cmd, t_wrapper *wrp);
void	unset_path_cmd(t_wrapper *wrp, int i);
void	ft_only_cmd(t_wrapper *wrp, int i);

char	*get_path(t_list *env);
char	*absolute_path(char *cmd, char **s_path);
int	check_first(char **s_path, char *cmd);
char	*free_ret(char *str1, char *str2, char *to_ret);


t_redir		*ft_hook_in(t_list *redir);
t_redir		*ft_hook_out(t_list *redir);
t_list	*ft_hook(t_list *redir);
void	ft_redir_cmd(t_wrapper *wrp, int i);
void    unset_path_redir(t_wrapper *wrp);
void	ft_unset_path_builtin(t_wrapper *wrp, int stats);
void    exec_cmd_redir(t_wrapper *wrp, char **split_path, int i);
void    exec_builtin_redir(t_wrapper *wrp);


void	ft_dup_out_redir(t_list *redir, int file);
void	ft_is_redirection(t_list *redir);
void	ft_in_redir(t_list *redir);
void	ft_out_redir(t_list *redir);
void	ft_append_redir(t_list *redir);
void	execute(t_wrapper *wrp);

int		check_for_heredoc(t_wrapper *wrp);
void	ft_here_doc(t_wrapper *wrp, char *filename);
void	ft_open_heredoc(t_wrapper *wrp);
char	*ft_random_name(char *filename);

void	ft_pipe_cmd_only(t_wrapper *wrp);
void	ft_pipe_cmd_redir(t_wrapper *wrp);
void	ft_exec_pipe_redir(t_wrapper *wrp);
void	ft_exec_pipe_redir_2(t_wrapper *wrp);
void	ft_pipe(t_wrapper *wrp);
void	ft_pipes_loop(t_wrapper *wrp);

#endif