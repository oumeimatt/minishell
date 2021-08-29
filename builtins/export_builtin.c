/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:02:40 by oel-yous          #+#    #+#             */
/*   Updated: 2021/08/29 14:31:29 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*print_quotes(char *str, char *temp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		temp[j] = str[i];
		if (str[i] == '=')
		{
			temp[j++] = str[i++];
			temp[j] = '"';
			j++;
			while(str[i] != '\0')
				temp[j++] = str[i++];
			if (str[i] == '\0')
				break;
		}
		i++;
		j++;
	}
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
	temp = (char*)malloc(sizeof(char) * (length + 3));
	if (!temp)
		return (NULL);
	return (print_quotes(str, temp));
}

void	only_export(t_list *env)
{
	t_list	*tmp;
	char	*str;

	tmp = env;
	while (tmp != NULL)
	{
		if (!ft_strcmp(((t_env *)(tmp->data))->value, "_"))
		{
			if (tmp->next == NULL)
				return ;
			else
				tmp = tmp->next;
		}
		if (tmp->next == NULL)
        {		
            if (valid_export(((t_env *)(tmp->data))->value) == 2)
            {
				str = quotes_after_equal(((t_env *)(tmp->data))->value);
				ft_putstr_fd("declare -x ", 1);
				ft_putendl_fd(str, 1);
				free(str);
				str = NULL;
				return ;
            }
            else
            {
				ft_putstr_fd("declare -x ", 1);
				ft_putendl_fd(((t_env *)(tmp->data))->value, 1);
				return ;
			}
        }
		else
		{
			if (valid_export(((t_env *)(tmp->data))->value) == 2)
            {
				str = quotes_after_equal(((t_env *)(tmp->data))->value);
				ft_putstr_fd("declare -x ", 1);
				ft_putendl_fd(str, 1);
				free(str);
				str = NULL;
				tmp = tmp->next;
            }
            else
            {
				ft_putstr_fd("declare -x ", 1);
				ft_putendl_fd(((t_env *)(tmp->data))->value, 1);
			}
		}
	}
}

int		valid_export(char *str)
{
	int	i;

	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
		return (1);
	i = 1;
	while(str[i] != '\0')
	{
		if (str[i] != '=')
		{
			if (ft_isalpha(str[i]) == 0 &&
				ft_isdigit(str[i]) == 0 && str[i] != '_')
				return (1);
		}
		else
			return (2);
		i++;
	}
	return (0);
}

void	export_error(char *str)
{
	ft_putstr_fd("petitshell: export: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_vars.i = 1;
}

void	export_builtin(char **str, t_list *env, int i)
{
	int		j;
	char	*line;
	char	*string;
	char	*key;
	int 	egal;

	j = 0;
	egal = 0;
	string = str[i];
	line = ft_strdup("");
	key = ft_strdup("");
	while (string[j] != '=' && string[j] != '\0')
		key = ft_charjoin(key, string[j++]);
	while (string[j] != '\0')
	{
		if (string[j] == '=')
			egal = 1;
		line = ft_charjoin(line, string[j++]);
	}
	line = check_quotes(line);
	line = ft_strjoin(key, line);
	if (!is_key_exist(env, key) && egal == 1)
	{
		delete_node_env(&env, key);
		addback_list(&env, new_list((t_env *)new_env(key, line)));
	}
	else if (!is_key_exist(env, key) && egal == 0)
		return ;
	else if (is_key_exist(env, key))
		addback_list(&env, new_list((t_env *)new_env(key, line)));
	free(key);
	key = NULL;
}
void	exec_export(char **str, t_list *env, int x)
{
	int		i;

	if (str[1] != NULL)
	{
		i = 1;
		while (str[i] != NULL)
		{
			if (valid_export(str[i]) == 1)
			{
				export_error(str[i]);
				i++;
			}
			else
			{
				export_builtin(str, env, i);
				i++;
			}
		}
		if (x == 1)
			exit(0);
	}
	if (str[1] == NULL)
	{
		only_export(env);
		if (x == 1)
			exit(0);
	}
}
