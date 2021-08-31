/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 18:06:21 by oel-yous          #+#    #+#             */
/*   Updated: 2021/08/31 16:43:22 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// char	*get_path(t_list **env)
// {
// 	int		i;
// 	char	*line;
// 	t_list *tmp;

// 	tmp = *env;
// 	i = 0;
// 	line = NULL;
// 	while (tmp->next != NULL)
// 	{
// 		if (!ft_strncmp(((t_env *)(tmp->data))->key, "PATH", 4))
// 			line = ft_strdup(((t_env *)(tmp->data))->value);
// 		tmp = tmp->next;
// 	}
// 	return (line);
// }

char	*free_ret(char *str, char *to_ret)
{
	if (str)
	{
		free(str);
		str = NULL;
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

	if (cmd[0] == '/' || cmd[0] == '.')
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
	free(cmd);
	if (acc == 0)
		return (free_ret(failed, commande));
	else
		return (free_ret(commande, failed));
}

char	*ft_cmd_path(char *cmd, char *full_path)
{
	char	**sp_path;

	sp_path = ft_split_2(full_path, ':');
	return (absolute_path(cmd, sp_path));
}