#include "parser.h"

void			ext_parse_tokens(t_list **pipeline, char **tab)
{
	int	i;
	char	**tmp;
	t_command cmd;

	i = 0;
	while (tab[i])
	{
/* 		if (ft_strncmp(tab[i], "export", 6) && ft_strncmp(tab[i], "<<", 2))
			tab[i] = quotes_reformat(tab[i]); */
		tmp = ft_split2(tab[i], ' ');
		if (ft_strcmp(tmp[0], "<<") && ft_strcmp(tmp[0], "export"))
			tab_trimmer(tmp);
		ext2_parse_tokens(&cmd, tmp);
		addback_list(pipeline, new_list((t_command *)new_command(cmd.tokens, cmd.redir)));
		destroy_tab(tmp, 0);
		i++;
	}
}

void			ext2_parse_tokens(t_command *cmd, char **tab)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	cmd->redir = NULL;
	cmd->tokens = malloc(sizeof(char *) * 1024);
	while (tab[i])
	{
		if (!flag && !ext3_parse_tokens(cmd, tab, i, &flag))
		{	
			cmd->tokens[j] = ft_strdup(tab[i]);
			j++;
		}
		skip_flag(&flag);
		i++;
	}
	cmd->tokens[j] = NULL;
}

static void		ext_parse_redir(t_command *cmd, char **tab, int i, int **flag)
{
	if (!ft_strcmp(tab[i], "<"))
		addback_list(&(cmd->redir), new_list((t_redir *)new_redir(1, ft_strdup(tab[i + 1]))));
	else if (!ft_strcmp(tab[i], "<<"))
		addback_list(&(cmd->redir), new_list((t_redir *)new_redir(2, ft_strdup(tab[i + 1]))));
	**flag = 2;	
}

static void		ext2_parse_redir(t_command *cmd, char **tab, int i, int **flag)
{
	if (!ft_strcmp(tab[i], ">"))
		addback_list(&(cmd->redir), new_list((t_redir *)new_redir(3, ft_strdup(tab[i + 1]))));
	else if (!ft_strcmp(tab[i], ">>"))
		addback_list(&(cmd->redir), new_list((t_redir *)new_redir(4, ft_strdup(tab[i + 1]))));
	**flag = 2;	
}

int			ext3_parse_tokens(t_command *cmd, char **tab, int i, int *flag)
{
	if (!ft_strcmp(tab[i], "<") || !ft_strcmp(tab[i], "<<"))
	{
		ext_parse_redir(cmd, tab, i, &flag);
		return (1);
	}
	else if (!ft_strcmp(tab[i], ">") || !ft_strcmp(tab[i], ">>"))
	{
		ext2_parse_redir(cmd, tab, i, &flag);
		return (1);
	}
	return (0);	
}
