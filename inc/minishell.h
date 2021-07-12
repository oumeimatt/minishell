/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:03:42 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/12 14:10:16 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h> 
# include <unistd.h>
#include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

# define STDOUT 1
# define STDIN 0
# define STDERR 2
# define MAX_INT 2147483647
# define BHBLK "\e[1;90m"
# define BHRED "\e[1;91m"
# define BHGRN "\e[1;92m"
# define BHYEL "\e[1;93m"
# define BHBLU "\e[1;94m"
# define BHMAG "\e[1;95m"
# define BHCYN "\e[1;96m"
# define BHWHT "\e[1;97m"
# define reset "\e[0m"


/** execution typedefs**/
# define TRUE 0
# define FALSE 1

typedef struct 		s_env
{
	char            *key; 
	char            *value; 
	struct s_env    *next;
}			t_env;

int		g_i;
/** execution **/
/*********************/
/* parsing typedefs */

typedef struct		s_error
{
	int		errnum;
	char	*errmsg;
}					t_error;

typedef struct		s_lstredir
{
	int		type;
	char		*filename;
	struct s_lstredir *next;
}			t_lstredir;

typedef struct		iofiles
{
	char **infile;
	char **outfile;
	char **tokens;
	t_lstredir *redir;
}			t_iofiles;

typedef struct 		s_cmd
{
    char    **tokens;
	pid_t	pid;
	int		redir;
}              		t_cmd;

typedef struct 		s_pipeline
{
	t_cmd		cmd;
	int		in;
	int		out;
	t_lstredir *redir;
	struct s_pipeline *next;
}			t_pipeline;

typedef struct		s_wrapper
{
	t_pipeline	*pipeline;
	t_env		*env;
	t_error		*error;
}			t_wrapper;

/*parsing*/
/********************/


/****parsing prototypes******/

t_lstredir		*lstredir_last(t_lstredir *lst);
t_lstredir		*lstredir_new(int type, char *filename);
int			lstredir_size(t_lstredir *lst);
void			lstredir_addback(t_lstredir **alst, t_lstredir *lst);
void			lstredir_debug(t_lstredir *lst);
/*							*/

/*							*/
t_cmd			cmd_create(char **tokens);
void			cmd_destroy(t_cmd *cmd);
t_wrapper		*contruct_wrapper(void);
/*							*/

/*							*/
t_pipeline		*pipeline_last(t_pipeline *lst);
t_pipeline		*pipeline_new(t_cmd cmd, t_lstredir *redir);
int			pipeline_size(t_pipeline *lst);
void			pipeline_addback(t_pipeline **alst, t_pipeline *lst);
void			pipeline_debug(t_pipeline *lst);
/*							*/

/*							*/
void			parser(t_wrapper *wrp, char **envp);
int				parser_line(t_wrapper *wrp);
void			parser_tokens(t_wrapper *wrp, char *line);
void			parser_tab_checker(t_wrapper *wrp, char **tab, t_iofiles *iofiles);
/*							*/

/*							*/
int				get_len_env(char *string);
char			*expand_env(t_wrapper *wrp, char *string);
char 			*reformat_line(t_wrapper *wrp, char *line);
char 			*redirection_reformat(const char *string);
char			*pipes_reformat(char *line);
char			*print_prompt(char **line);
int				check_line_syntax(char *string);
int				check_line_syntax2(char *string);
int				check_line_syntax3(char *string);
/*							*/

/*							*/
void			put_err(t_wrapper *wrp);
void			load_msg_err(t_wrapper *wrp, int flag);
const char 			*get_prompt(t_wrapper *wrp);
/*							*/

/*							*/
void			debug_tab(char **tab);
void			destroy_tab(char **tab);
int			is_redir(char c);
void			tab_trimmer(char **tab);
int			tab_len(char **tab);
int			exists_in_tab(char *s, char **tab);
int			index_of_in_tab(char *s, char **tab);
int			free_s_tab(char **tab);
int			max_v(int a, int b);
int			min_v(int a, int b);

/****parsing prototypes******/

/** execution prototypes **/

t_env   *change_value(t_env *env, char *key, char *value);
void    cd_only(char *buff, t_env *env, char *oldpwd);
void    exec_cd(char **str, t_env *env, int i);
int		echo_valid_option(char *str);
void	echo_option_exist(char **str);
void   exec_echo(char **str, int i);
void    exec_env(t_env *env, int i);
int     is_key_exist(t_env *env, char *key);
t_env	*init_env(char **envp, t_env *list);
char	*print_quotes(char *str, char *temp);
char	*quotes_after_equal(char *str);
void	only_export(t_env *env);
int		valid_export(char *str);
void	export_error(char *str);
void	export_builtin(char **str, t_env *env, int i);
void	exec_export(char **str, t_env *env, int i);
int    is_builtin(char **str);
char    *pwd_builtin();
void	exec_pwd(int i);
void    unset_error(char *str);
void    exec_unset(char **str, t_env *env, int i);
void	ft_add_node(t_env **head_ref, char *line, char *key);
void	delete_node(t_env **head_ref, char *key);
void    print_list(t_env *head);
char    *print_value(t_env *env, char *key);
int		ft_strcmp(const char *s1, const char *s2);
char    *ft_charjoin(char *str, char c);
void    exec_exit();
void    exec_cmd(char **str);
char	*get_path(t_env *env);
char	**ft_split_2(char const *str, char c);
char	**ft_return(char **tab, int number_words);
void	initial(int *i, int *j);
int	ft_add_word(char **tab, char const *str, int *nb_word, int c);
int	ft_word(char const *str, int i, int *nb_word, int c);
char	*free_ret(char *str1, char *str2, char *to_ret);
int	check_first(char **s_path, char *cmd);
char	*absolute_path(char *cmd, char **s_path);
void	ft_only_cmd(t_wrapper *wrp, int i);
void	ft_is_redirection(t_lstredir *redir, int i);
void	ft_in_redir(t_lstredir *redir, int i);
void	ft_here_doc(t_lstredir *redir);
void	ft_redir_cmd(t_wrapper *wrp, int i);
void	ft_out_redir(t_lstredir *redir, int i);
void	ft_append_redir(t_lstredir *redir, int i);
int		ft_read(int fd, char **str);
int		ft_remplissage(char **str, char **line, int len);
int		ft_finish(char **str, char **line);
int		get_next_line(int fd, char **line);
int		count_redir(t_lstredir *redir, int type);
void	ft_hd_redir(int i);
void    exec_builtin(char **str, t_env *env, int i) ;
void	unset_path_cmd(t_wrapper *wrp, int i);
void    exec_cmd_redir(t_wrapper *wrp, char **split_path, int i);
void    exec_builtin_redir(t_wrapper *wrp);
void    unset_path_redir(t_wrapper *wrp, int i);
void	ft_pipes_loop(t_wrapper *wrp);
void    ft_pipe_cmd_only(t_wrapper *wrp);
void	ft_pipe_cmd_redir(t_wrapper *wrp);
void	ft_pipe(t_wrapper *wrp);

/** execution prototypes **/
#endif