/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:02:40 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/06 13:06:25 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing/inc/minishell.h"

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

void	only_export(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->value, "_") == TRUE)
		{
			if (tmp->next == NULL)
				return ;
			else
				tmp = tmp->next;
		}
		if (tmp->next == NULL)
        {		
            if (valid_export(tmp->value) == 2)
            {
                printf("declare -x %s\n", quotes_after_equal(tmp->value));
				return ;
            }
            else
            {
				printf("declare -x %s\n", tmp->value);
				return ;
			}
        }
		else
		{
			if (valid_export(tmp->value) == 2)
            {
                printf("declare -x %s\n", quotes_after_equal(tmp->value));
				tmp = tmp->next;
            }
            else
            {
				printf("declare -x %s\n", tmp->value);
				tmp = tmp->next;
			}
		}
	}
}

int		valid_export(char *str) /// valid export returns 2 if there's "=" in str
{
	int	i;

	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
		return (FALSE);
	i = 0;
	while(str[i] != '\0')
	{
		if (str[i] != '=')
		{
			if (ft_isalpha(str[i]) == 0 &&
				ft_isdigit(str[i]) == 0 && str[i] != '_')
				return (FALSE);
		}
		else
			return (2);
		i++;
	}
	return (TRUE);
}

void	export_error(char *str)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	export_builtin(char **str, t_env *env, int i)
{
	int		j;
	char	*line;
	char	*key;

	j = 0;
	line = str[i];
	key = ft_strdup("");
	while (line[j] != '=' && line[j] != '\0')
		key = ft_charjoin(key, line[j++]);
	if (is_key_exist(env, key) == TRUE)
	{
		delete_node(&env, key);
		ft_add_node(&env, line, key);
	}
	else
		ft_add_node(&env, line, key);
	free(key);
	key = NULL;
}
void	exec_export(char **str, t_env *env)
{
	int		i;

	if (str[1] != NULL)
	{
		i = 1;
		while (str[i] != NULL)
		{
			if (valid_export(str[i]) == FALSE)
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
	}
	if (str[1] == NULL)
		only_export(env);
}
