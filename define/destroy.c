#include "define.h"

void			destroy_env(t_env *env)
{
	free (env->key);
	env->key = NULL;
	free (env->value);
	env->value = NULL;
	free (env);
	env = NULL;
}

void			destroy_redir(t_redir *redir)
{
	free (redir->filename);
	redir->filename = NULL;
	free (redir);
	redir = NULL;
}

void			destroy_command(t_command *cmd)
{
	destroy_tab(cmd->tokens, 0);
	destroy_lredir(cmd->redir);
	free (cmd);
	cmd = NULL;
}