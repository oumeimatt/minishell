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
void	cd_only(char *buff, t_list **env, char *oldpwd);
void    exec_cd(char **str, t_list **env, int x);

int		echo_valid_option(char *str);
void	echo_option_exist(char **str);
void   exec_echo(char **str, int x);

void    exec_env(t_list **env, int x);
int     is_key_exist(t_list **env, char *key);

void    exec_exit(char **str);

char	*print_quotes(char *str, char *temp);
char	*quotes_after_equal(char *str);
void	only_export(t_list **env);
int	valid_export(char *str);
void	export_error(char *str);
void	export_builtin(char **str, t_list **env, int i);
void	exec_export(char **str, t_list **env, int x);

int		is_builtin(char	**str);
void    exec_builtin(char **str, t_list **env, int i); 

char    *pwd_builtin();
void	exec_pwd(t_list **env, int x);

void    unset_error(char *str);
void    exec_unset(char **str, t_list **env, int x);

char	*check_quotes(char *line);
char	*ft_single_quotes(char *line);
char	*ft_double_quotes(char *line);

char    *ft_charjoin(char *str, char c);
int	find_length(t_list *head);
char	**list_to_arr(t_list *head);

int	ft_word(char const *str, int i, int *nb_word, int c);
int	ft_add_word(char **tab, char const *str, int *nb_word, int c);
void	initial(int *i, int *j);
char	**ft_return(char **tab, int number_words);
char	**ft_split_2(char const *str, char c);


#endif