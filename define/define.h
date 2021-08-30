#ifndef DEFINE_H
# define DEFINE_H

# include "../list/list.h"
# include "../tools/tools.h"
# include "../libft/libft.h"
# include <stdio.h>

# define BHBLK "\e[1;90m"
# define BHRED "\e[1;91m"
# define BHGRN "\e[1;92m"
# define BHYEL "\e[1;93m"
# define BHBLU "\e[1;94m"
# define BHMAG "\e[1;95m"
# define BHCYN "\e[1;96m"
# define BHWHT "\e[1;97m"
# define reset "\e[0m"
# define TRUE 1
# define FALSE 0

typedef	struct	s_redir
{
	int	type;
	char	*filename;
}		t_redir;

typedef struct s_command
{
	char	**tokens;
	int	in;
	int	out;
	t_list	*redir;
}		t_command;

typedef struct s_env
{
	char	*key;
	char	*value;
}		t_env;

t_env			*new_env(char *key, char *value);
t_redir			*new_redir(int type, char *filename);
t_command		*new_command(char **tokens, t_list *redir);

void			destroy_env(t_env *env);
void			destroy_redir(t_redir *redir);
void			destroy_command(t_command *cmd);

void			destroy_lenv(t_list *lst);
void			destroy_lredir(t_list *lst);
void			destroy_lcommand(t_list *lst);

void			debug_env(t_list *env);
void			debug_redir(t_list *redir);
void			debug_pipeline(t_list *pipeline);

char			*get_value_env(t_list **env, char *value);
void			delete_node_env(t_list **env, char *key);

#endif
