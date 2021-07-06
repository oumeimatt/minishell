/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:03:42 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/06 15:07:35 by oel-yous         ###   ########.fr       */
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


/** execution **/
# define TRUE 0
# define FALSE 1

typedef struct      s_env
{
	char            *key; 
	char            *value; 
	struct s_env    *next;
}                   t_env;

/** execution **/
/**/
typedef struct	iofiles
{
	char **infile;
	char **outfile;
}	t_iofiles;
/**/

/*							*/
/*							*/

/*							*/
typedef struct s_cmd
{
    char    **tokens;
    char    **input_files;
    char    *output_files;
}               t_cmd;

t_cmd			cmd_create(char **tokens, char **in_files, char *out_files);
void			cmd_destroy(t_cmd *cmd);

/*							*/

/*							*/
typedef struct s_pipeline
{
	t_cmd	cmd;
	struct s_pipeline *next;
}				t_pipeline;

t_pipeline		*pipeline_last(t_pipeline *lst);
t_pipeline		*pipeline_new(t_cmd cmd);
int				pipeline_size(t_pipeline *lst);
void			pipeline_addback(t_pipeline **alst, t_pipeline *lst);
void			pipeline_debug(t_pipeline *lst);

/*							*/

/*							*/
typedef struct s_wrapper
{
	t_pipeline	*pipeline;
	t_env		*env;
}			t_wrapper;

void			new_outfile(t_wrapper wrp, char *instr);

void			parser(t_wrapper *wrp, char **envp);
void			parse_envp(t_wrapper *wrp, char **envp);
void			parse_line(t_wrapper *wrp);
void			parse_tokens(t_wrapper *wrp, char *line);
char			*print_prompt(char **line);
t_wrapper		*contruct_wrapper(void);
/*							*/
void			debug_tab(char **tab);
void			ft_env_var(t_wrapper *wrp, char **tab, int i, int flag);
int				GetTabSize(char **tab);
void			destroy_tab(char **tab);
void			tab_trimmer(char **tab);

void			tab_checker(t_wrapper *wrp, char **tab, t_iofiles *iofiles);
void			output_file(t_wrapper *wrp, char ** tab, int *index);



/*	*/
/*	*/

/**/
int		tab_len(char **tab);
int		exists_in_tab(char *s, char **tab);
int		index_of_in_tab(char *s, char **tab);
int		free_s_tab(char **tab);
char		**sub_tab(char **src, int i);
int			max_v(int a, int b);
int			min_v(int a, int b);



/** execution **/

t_env   *change_value(t_env *env, char *key, char *value);
void    cd_only(char *buff, t_env *env, char *oldpwd);
void    exec_cd(char **str, t_env *env);
int		echo_valid_option(char *str);
void	echo_option_exist(char **str);
void   exec_echo(char **str);
void    exec_env(t_env *env);
int     is_key_exist(t_env *env, char *key);
t_env	*init_env(char **envp, t_env *list);
char	*print_quotes(char *str, char *temp);
char	*quotes_after_equal(char *str);
void	only_export(t_env *env);
int		valid_export(char *str);
void	export_error(char *str);
void	export_builtin(char **str, t_env *env, int i);
void	exec_export(char **str, t_env *env);
void    is_builtin(char **str, t_env *env);
char    *pwd_builtin();
void	exec_pwd();
void    unset_error(char *str);
void    exec_unset(char **str, t_env *env);
void	ft_add_node(t_env **head_ref, char *line, char *key);
void	delete_node(t_env **head_ref, char *key);
void    print_list(t_env *head);
char    *print_value(t_env *env, char *key);
int		ft_strcmp(const char *s1, const char *s2);
char    *ft_charjoin(char *str, char c);

/** execution **/

#endif