#include "petitshell.h"

int	main(int argc, char **argv, char **envp)
{
	t_wrapper	wrp;

	if (argc == 1 && argv[0])
	{	
		parse_env(&(wrp.env), envp);
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		execution_loop(&wrp);
	}
	return (EXIT_SUCCESS);
}

void		execution_loop(t_wrapper *wrp)
{
	while (420)
	{
		if (parser(wrp)) //true means nothing is wrong with parsing Line.
		{
			/*hello oum*/
			/*execution*/
			execute(wrp);
			debug_pipeline(wrp->pipeline);
			destroy_lcommand(wrp->pipeline);
		}
	}
}