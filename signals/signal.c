#include "signal.h"

void			child_process(int signum)
{
	if (!kill(g_vars.pid, signum))
	{
		if (signum == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 1);
			g_vars.i = 131;
		}
		else if (signum == SIGINT)
		{
			ft_putchar_fd('\n', 1);
			g_vars.i = 130;
		}
	}
	else if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		ft_putchar_fd('\r', 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void			signal_handler(int signum)
{    
	if ((signum == SIGINT || signum == SIGQUIT) && g_vars.pid != 0)
		child_process(signum);
	else
	{	
		if (signum == SIGINT)
		{
			ft_putchar_fd('\n', 2);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay(); 
		}
		else if (signum == SIGQUIT)
		{
			ft_putchar_fd('\r', 2);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}