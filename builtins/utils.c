#include "builtins.h"

char    *ft_charjoin(char *str, char c)
{
	int l;
	char	*res;
	int i = 0;

	l = ft_strlen(str);
	res = malloc(l + 2);
	while (i < l)
	{
		res[i] = *str;
		str++;
		i++;
	}
	res[i] = c;
	res[i + 1] = '\0';
	return(res);
}

int	find_length(t_list *head)
{
	t_list	*current;
	int		count;

	current = head;
	count = 0;
	while (current != NULL) {
		count++;
		current = current->next;
	}
	return count;
}

char	**list_to_arr(t_list *head)
{
	int len;
	char **arr;

	len = find_length(head);
	arr = NULL;
	arr = malloc(sizeof (char **) * (len + 1));
	int index = 0;
	t_list *curr = head;
	while (curr != NULL) {
		arr[index++] = ft_strdup(((t_env *)(curr->data))->value);
		curr = curr->next;
	}
	arr[len] = NULL;
	return(arr);
}