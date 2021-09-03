#ifndef BUILTINS_H
# define BUILTINS_H

# include "../list/list.h"
# include "../define/define.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>

typedef struct s_vars
{
	int	i;
	int	pid;
}	t_vars;


extern t_vars	g_vars;

void	change_value(t_list **env, char *key, char *value);
void	cd_only(t_list **env);
void	exec_cd(char **str, t_list **env, int x);
void	help_exec_cd(char **str, char *oldpwd, t_list **env);

int		echo_valid_option(char *str);
void	echo_option_exist(char **str);
void	exec_echo(char **str, int x);

void	exec_env(t_list **env, int x);
int		is_key_exist(t_list **env, char *key);

void	export_error(char *str);
void	exec_export(char **str, t_list **env, int x);

int		valid_export(char *str);
char	*get_key(char *str);
char	*get_value(char *str);
void	replace_env_value(t_list **env, char *key, char *value);
void	export_builtin(char **str, t_list **env, int i);

char	*print_quotes(char *str, char *temp);
char	*quotes_after_equal(char *str);
void	display_export(t_list *env);
void	only_export(t_list **env);

char	*pwd_builtin(t_list **env);
void	exec_pwd(t_list **env, int x);

void	unset_error(char *str);
void	exec_unset(char **str, t_list **env, int x);

void    exec_exit(char **str);

int		is_builtin(char	**str);
void	exec_builtin(char **str, t_list **env, int i);

int		find_length(t_list *head);
char	**list_to_arr(t_list **head);
char	*free_ret(char *str, char *to_ret);

int		ft_word(char const *str, int i, int *nb_word, int c);
int		ft_add_word(char **tab, char const *str, int *nb_word, int c);
void	initial(int *i, int *j);
char	**ft_return(char **tab, int number_words);
char	**ft_split_2(char const *str, char c);


#endif