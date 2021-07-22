#include "../inc/minishell.h"

int	find_length(t_env    *head)
{
	t_env	*current;
	int		count;

	current = head;
	count = 0;
	while (current != NULL) {
		count++;
		current = current->next;
	}
	return count;
}

char **list_to_arr(t_env *head)
{
    int len;
	char **arr;

	len = find_length(head);
	arr = NULL;
	arr = malloc(sizeof (char **) * (len + 1));
    int index = 0;
   	t_env *curr = head;
 
    while (curr != NULL) {
        arr[index++] = ft_strdup(curr->value);
        curr = curr->next;
    }
	arr[len] = NULL;
	return(arr);
}
