#include "parser.h"

void			put_err(t_wrapper *wrp)
{
	if (wrp->error.errnum <= -1)
		ft_putstr_fd(wrp->error.errmsg, 2);
	fill_exit_code(wrp);
	free (wrp->error.errmsg);
}

void			load_msg_err(t_wrapper *wrp, int flag)
{
	wrp->error.errnum = flag;
	if (flag == -1)
		wrp->error.errmsg = ft_strdup("minishell: syntax error near unexpected token `|'\n");
	else if (flag == -2)
		wrp->error.errmsg = ft_strdup("minishell: syntax error near unexpected token `||'\n");
	else if (flag == -3)
		wrp->error.errmsg = ft_strdup("minishell: syntax error near unexpected token `newline'\n");
	else if (flag == -4)
		wrp->error.errmsg = ft_strdup("minishell: syntax error near unexpected token `>'\n");
	else if (flag == -5)
		wrp->error.errmsg = ft_strdup("minishell: syntax error near unexpected token `>>'\n");
	else if (flag == -6)
		wrp->error.errmsg = ft_strdup("minishell: syntax error near unexpected token `<'\n");
	else if (flag == -7)
		wrp->error.errmsg = ft_strdup("minishell: syntax error near unexpected token `<<'\n");
	else if (flag == 0)
		wrp->error.errmsg = ft_strdup("");
}

void		fill_exit_code(t_wrapper *wrp)
{
	if (wrp->error.errnum >= -7 && wrp->error.errnum <= -1)
	{
		g_vars.i = 258;
	}
}