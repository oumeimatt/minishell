#include "parser.h"

void			destroy_wrapper(t_wrapper *wrp)
{
	destroy_lenv(wrp->env);
	destroy_lcommand(wrp->pipeline);
}