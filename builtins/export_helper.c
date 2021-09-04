/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:29:08 by oel-yous          #+#    #+#             */
/*   Updated: 2021/09/04 12:02:53 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	valid_export(char *str)
{
	int	i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	i = 1;
	while (str[i] != '=' && str[i] != '\0')
	{
		if ((!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_'))
			return (1);
		i++;
	}
	return (0);
}

char	*get_key(char *str)
{
	int		i;
	char	*key;

	key = malloc(ft_strlen(str) + 1);
	i = 0;
	while (str[i] != '=' && str[i] != '\0')
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*get_value(char *str)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	value = malloc(ft_strlen(str));
	while (str[i] != '\0')
	{
		if (str[i] != '=')
			i++;
		else
			break ;
	}
	j = 0;
	while (str[i] != '\0')
		value[j++] = str[i++];
	value[j] = '\0';
	return (value);
}

void	replace_env_value(t_list **env, char *key, char *value)
{
	t_list	*tmp;

	tmp = *env;
	if (!is_key_exist(&tmp, key) && value[0] == '\0')
		return ;
	else if (!is_key_exist(&tmp, key))
	{
		delete_node_env(&tmp, key);
		addback_list(&tmp, new_list((t_env *)new_env(key, value)));
	}
	else if (is_key_exist(&tmp, key))
		addback_list(&tmp, new_list((t_env *)new_env(key, value)));
}

void	export_builtin(char **str, t_list **env, int i)
{
	int		j;
	char	*value;
	char	*key;

	j = 0;
	value = NULL;
	key = get_key(str[i]);
	value = get_value(str[i]);
	replace_env_value(env, key, value);
	free_ret(key, NULL);
	free_ret(value, NULL);
}
