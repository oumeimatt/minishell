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
		if (parser(wrp))
		{
			//debug_pipeline(wrp->pipeline);
			execute(wrp);
			destroy_lcommand(wrp->pipeline);
		}
	}
}