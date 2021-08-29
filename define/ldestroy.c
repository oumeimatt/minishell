#include "define.h"

void		destroy_lenv(t_list *lst)
{
	t_list *next;
	t_list *current;

	if (!lst)
		return ;
	current = lst;
	while (current != NULL)
	{
		next = current->next;
		destroy_env((t_env *)(current->data));
		free (current);
		current = next;
	}
	lst = NULL;
}

void			destroy_lredir(t_list *lst)
{
	t_list *next;
	t_list *current;

	if (!lst)
		return ;
	current = lst;
	while (current != NULL)
	{
		next = current->next;
		destroy_redir((t_redir *)(current->data));
		free (current);
		current = next;
	}
	lst = NULL;
}

void			destroy_lcommand(t_list *lst)
{
	t_list *next;
	t_list *current;

	if (!lst)
		return ;
	current = lst;
	while (current != NULL)
	{
		next = current->next;
		destroy_command((t_command *)(current->data));
		free (current);
		current = next;
	}
	lst = NULL;
}