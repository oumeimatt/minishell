/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 18:06:21 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/06 19:07:21 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_path(t_env *env)
{
	int		i;
	char	*line;
    t_env *tmp;

    tmp = env;
	i = 0;
	line = NULL;
	while (tmp->next != NULL)
	{
		if (ft_strncmp(tmp->key, "PATH", 4) == TRUE)
			line = ft_strdup(tmp->value + ft_strlen(tmp->key) + 1);
		tmp = tmp->next;
	}
	return (line);
}

char	*free_ret(char *str1, char *str2, char *to_ret)
{
	if (str1)
	{
		free(str1);
		str1 = NULL;
	}
	if (str2)
	{
		free(str2);
		str2 = NULL;
	}
	return (to_ret);
}

int	check_first(char **s_path, char *cmd)
{
	char	*first;
	int		acc;
	char	*tmp;
	char	*commande;

	first = s_path[0] + 5;
	tmp = ft_strjoin(first, "/");
	commande = ft_strjoin(tmp, cmd);
	acc = access(commande, F_OK);
	if (acc != 0)
	{
		free(tmp);
		free(commande);
	}
	return (acc);
}

char	*absolute_path(char *cmd, char **s_path)
{
	int		i;
	char	*tmp;
	char	*commande;
	int		acc;
	char	*failed;

	if (cmd[0] == '/')
		return (cmd);
	failed = ft_strdup(cmd);
	i = 0;
	acc = check_first(s_path, cmd);
	while (acc != 0 && s_path[++i] != NULL)
	{
		tmp = ft_strjoin(s_path[i], "/");
		commande = ft_strjoin(tmp, cmd);
		acc = access(commande, F_OK);
		if (acc != 0 && s_path[i + 1] != NULL)
			free(commande);
		free(tmp);
	}
	if (acc == 0)
		return (free_ret(cmd, failed, commande));
	else
		return (free_ret(cmd, commande, failed));
}
