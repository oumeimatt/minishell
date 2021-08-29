#ifndef PETITSHELL_H
# define PETITSHELL_H

# include "../parser/parser.h"
# include "../list/list.h"
# include "../libft/libft.h"
# include "../signals/signal.h"
# include "../builtins/builtins.h"
# include "../execution/execution.h"

void		execution_loop(t_wrapper *wrp);

#endif