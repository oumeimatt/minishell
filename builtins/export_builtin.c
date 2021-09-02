/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:02:40 by oel-yous          #+#    #+#             */
/*   Updated: 2021/09/02 18:06:32 by oel-yous         ###   ########.fr       */
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
	temp = (char*)malloc(sizeof(char) * (length + 3));
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
		if (!ft_strcmp(((t_env *)(tmp->data))->key, "_") && 
			!((t_env *)(tmp->data))->value)
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
			break;
	}
}

int		valid_export(char *str)
{
	int	i;

	if (!ft_isalpha(str[0]) && str[0] != '_' &&
		str[0] != '\'' && str[0] != '"')
		return (1);
	i = 1;
	while(str[i] != '=' && str[i] != '\0')
	{
		if (!ft_isalpha(str[i]) &&
			!ft_isdigit(str[i]) && str[i] != '_' &&
			str[i] != '\'' && str[i] != '"')
				return (1);
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

char	*skip_key_quotes(char *str, char *key, int s_q, int d_q)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '=' && str[i] != '\0')
	{
		if (s_q == 1)
		{
			if (str[i] == '\'')
				i++;
		}
		else if (d_q == 1)
		{
			if (str[i] == '"')
				i++;
		}
		if (str[i] == '\0' || str[i] == '=')
			break;
		key[j++] = str[i++];
	}
	key[j] = '\0';
	return (key);
}

char	*get_key(char *str)
{
	int		i;
	int		s_q;
	int		d_q;
	char	*key;

	i = 0;
	s_q = 0;
	d_q = 0;
	while (str[i] != '=' && str[i] != '\0')
	{
		if (str[i] == '\'' && d_q == 0)
			s_q = 1;
		if (str[i] == '"' && s_q == 0)
			d_q = 1;
		i++;
	}
	key = malloc(i + 1);
	return (skip_key_quotes(str, key, s_q, d_q));
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
	char	*env_value;

	tmp = *env;
	env_value = ft_strjoin("=", value);
	if (!is_key_exist(&tmp, key))
	{
		delete_node_env(&tmp, key);
		addback_list(&tmp, new_list((t_env *)new_env(key, value)));
	}
	else if (!is_key_exist(&tmp, key) && ((t_env *)(tmp->data))->value == NULL)
	{
		free_ret(env_value, NULL);
		return ;
	}
	else if (is_key_exist(&tmp, key))
		addback_list(&tmp, new_list((t_env *)new_env(key, value)));
	free_ret(env_value, NULL);
}
// export a="s"s's"  
void	export_builtin(char **str, t_list **env, int i)
{
	int		j;
	char	*value; 
	char	*key;
	char	*tmp_value;

	j = 0;
	value = NULL;
	tmp_value = NULL;
	key = get_key(str[i]);
	tmp_value = get_value(str[i]);
	if (tmp_value[0] != '\0')
		value = check_quotes(tmp_value);
	replace_env_value(env, key, value);
	free_ret(tmp_value, NULL);
	free_ret(key, NULL);
	free_ret(value, NULL);
}

void	exec_export(char **str, t_list **env, int x)
{
	int		i;

	if (str[1] != NULL)
	{
		i = 1;
		while (str[i] != NULL)
		{
			if (valid_export(str[i]) == 1)
				export_error(str[i]);
			else
				export_builtin(str, env, i);
			i++;
		}
		if (x == 1)
			exit(0);
	}
	else
	{
		only_export(env);
		if (x == 1)
			exit(0);
	}
}
