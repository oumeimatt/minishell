#ifndef TOOLS_H
# define TOOLS_H

# include "../libft/libft.h"
# include "../builtins/builtins.h"
# include <stdlib.h>
# include <stdio.h>

void			destroy_tab(char **tab, int n);
void			tab_trimmer(char **tab);
char			*ext_tab_trimmer(char *string);

void			debug_tab(char **tab);


int			is_line(char *line);
char 			*redirection_reformat(const char *string);
char		*ext_redir(const char *string);
int			get_len_env(char *string);
char			*pipes_reformat(char *line);
char			*dquotes_reformat(char *line);
char			*spaces_dquotes_reformat(char *line);
char			*spaces_dquotes_reformat2(char *line);
int			check_line_syntax(char *string);
int			check_line_syntax2(char *string);
int			check_line_syntax3(char *string);
char			*quotes_reformat(char *line);
int			export_check_quotes(char *line);
int			is_redir(char c);
char			*expand_exit_code(char *string);
int			dollar_valid(char c);

int			spaces(char *line);

#endif