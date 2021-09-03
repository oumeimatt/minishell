#include "define.h"

t_command		*new_command(char **tokens, t_list *redir)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (0);
	cmd->tokens = tokens;
	cmd->redir = redir;
	return (cmd);
}

t_redir			*new_redir(int type, char *filename)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (0);
	redir->type = type;
	redir->filename = filename;
	return (redir);
}

t_env			*new_env(char *key, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (0);
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	return (env);
}

char			*get_value_env(t_list **env, char *value)
{
	t_list	*temp;

	temp = *env;
	while (temp != NULL)
	{
		if (!ft_strcmp(value, ((t_env *)(temp->data))->key))
			return (((t_env *)(temp->data))->value);
		if (temp->next)
			temp = temp->next;
		else
			break ;
	}
	return (NULL);
}

void	delete_node_env(t_list **env, char *key)
{
	t_list *temp;
	t_list *prev;

	temp = *env;
	if (temp != NULL && !strcmp(((t_env *)(temp->data))->key, key)) 
	{
		*env = temp->next;
		destroy_env((t_env *)temp->data);
		free(temp);
		return;
	}
	while (temp != NULL && strcmp(((t_env *)(temp->data))->key, key))
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return;
	prev->next = temp->next;
	destroy_env((t_env *)temp->data);
	free(temp);
}