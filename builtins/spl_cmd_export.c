/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:23:47 by oel-yous          #+#    #+#             */
/*   Updated: 2021/09/03 15:35:23 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*print_quotes(char *str, char *temp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp[j++] = str[i++];
	temp[j++] = '"';
	while (str[i] != '\0')
		temp[j++] = str[i++];
	temp[j] = '"';
	temp[j + 1] = '\0';
	return (temp);
}

char	*quotes_after_equal(char *str)
{
	int		length;
	char	*temp;

	length = 0;
	while (str[length] != '\0')
		length++;
	if (!str)
		return (NULL);
	temp = (char *)malloc(sizeof(char) * (length + 3));
	if (!temp)
		return (NULL);
	return (print_quotes(str, temp));
}

void	display_export(t_list *env)
{
	char	*str;

	if (((t_env *)(env->data))->value)
	{
		ft_putstr_fd("declare -x ", 1);
		str = quotes_after_equal(((t_env *)(env->data))->value);
		ft_putstr_fd(((t_env *)(env->data))->key, 1);
		ft_putendl_fd(str, 1);
		free_ret(str, NULL);
	}
	else
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(((t_env *)(env->data))->key, 1);
	}
}

void	only_export(t_list **env)
{
	t_list	*tmp;

	tmp = *env;
	while (tmp != NULL)
	{
		if (!ft_strcmp(((t_env *)(tmp->data))->key, "_")
			&& !((t_env *)(tmp->data))->value)
		{
			if (tmp->next == NULL)
				return ;
			else
				tmp = tmp->next;
		}
		display_export(tmp);
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
}
