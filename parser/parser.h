#ifndef PARSER_H
# define PARSER_H

# include "../list/list.h"
# include "../libft/libft.h"
# include "../define/define.h"
# include "../tools/tools.h"
# include "../builtins/builtins.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct	s_error
{
	int	errnum;
	char	*errmsg;
}		t_error;

typedef struct s_wrapper
{
	t_list	*pipeline;
	t_list	*env;
	t_error	error;
}		t_wrapper;

//	if (parser) procced to execution
int			parser(t_wrapper *wrp);

void			parse_env(t_list **env, char **envp);

int			is_line(char *line);
void			ctrl_d(t_wrapper *wrp, char *line);
char			*reformat_line(t_wrapper *wrp, char *line);
char			*expand_env(t_wrapper *wrp, char *string);
int			check_line(t_wrapper *wrp, char *line);

void			parse_tokens(t_list **pipeline, char *line);
void			ext_parse_tokens(t_list **pipeline, char **tab);
void			ext2_parse_tokens(t_command *cmd, char **tab);
int			ext3_parse_tokens(t_command *cmd, char **tab, int i, int *flag);
void			ext4_parse_tokens(t_command *cmd, char **tab, int i, int *j);
void			skip_flag(int *flag);


void			put_err(t_wrapper *wrp);
void			load_msg_err(t_wrapper *wrp, int flag);
void			fill_exit_code(t_wrapper *wrp);

void			destroy_wrapper(t_wrapper *wrp);
#endif