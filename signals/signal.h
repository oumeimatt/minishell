#ifndef SIGNAL_H
# define SIGNAL_H

# include "../libft/libft.h"
# include "../builtins/builtins.h"
# include <signal.h>
# include <readline/readline.h>

void			signal_handler(int signum);
void			child_process(int signum);

#endif