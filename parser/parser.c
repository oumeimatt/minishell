/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 13:46:23 by ztaouil           #+#    #+#             */
/*   Updated: 2021/09/05 16:41:26 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_env(t_list **env, char **envp)
{
	int		i;
	char	*key;

	i = 0;
	*env = NULL;
	while (envp[i] != NULL)
	{
		key = ft_substr(envp[i], 0, (ft_strchr(envp[i], '=') - envp[i]));
		addback_list(env,
			new_list((t_list *)new_env(key, envp[i] + ft_strlen(key))));
		free (key);
		i++;
	}
}

void	parse_tokens(t_list **pipeline, char *line)
{
	char	**tab;

	tab = ft_split(line, '|');
	*pipeline = NULL;
	ext_parse_tokens(pipeline, tab);
	destroy_tab(tab, 0);
}

int	parser(t_wrapper *wrp)
{
	char	*line;

	line = readline(BHBLU "petitshell-1.0" RESET BHWHT "$ " RESET);
	if (!is_line(line))
		return (0);
	ctrl_d(wrp, line);
	line = reformat_line(wrp, line);
	if (!check_line(wrp, line))
		return (0);
	return (1);
}
