#include "parser.h"

int			check_line(t_wrapper *wrp, char *line)
{
	if (line == NULL)
	{
		put_err(wrp);
		return (0);
	}
	else
	{
		parse_tokens(&(wrp->pipeline), line);
		free (line);
		line = NULL;
		return (1);
	}
}

void			skip_flag(int *flag)
{
	if (*flag >= 1)
		*flag -= 1;
	else if (!(*flag))
		*flag = 0;
}

void			ctrl_d(t_wrapper *wrp, char *line)
{
	if (!line)
	{
		(void)wrp;
		ft_putendl_fd("exit", 2);
		destroy_lenv(wrp->env);
		free (line);
		exit (0);
	}
}
