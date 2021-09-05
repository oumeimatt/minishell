/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 13:55:36 by ztaouil           #+#    #+#             */
/*   Updated: 2021/09/04 15:53:05 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

static int	ext_init(t_reform *env, const char *string)
{
	env->quote = 0;
	env->s_count = 0;
	env->p_count = 0;
	env->str = (char *)malloc(sizeof(char) * ft_strlen(string) * 10);
	if (!env->str)
		return (0);
	return (1);
}

static char	*return_free(t_reform env, const char *string)
{
	env.str[(env.s_count)] = '\0';
	free ((void *)string);
	env.str = ext_redir(env.str);
	return (env.str);
}

char	*redirection_reformat(const char *string)
{
	t_reform	env;

	if (!ext_init(&env, string))
		return (NULL);
	while (string[(env.p_count)] != '\0')
	{
		if (norm_help1(env, string))
			env.quote = 1;
		else if (norm_help2(env, string))
			env.quote = 0;
		if (norm_help3(env, string))
		{
			env.str[(env.s_count)++] = string[(env.p_count)++];
			env.str[(env.s_count)++] = ' ';
		}
		if (is_redir(string[(env.p_count)])
			&& !is_redir(string[(env.p_count) + 1])
			&& env.quote == 0 && !is_redir((env.p_count) - 1))
		{
			env.str[(env.s_count)++] = string[(env.p_count)++];
			env.str[(env.s_count)++] = ' ';
		}
		env.str[(env.s_count)++] = string[(env.p_count)++];
	}
	return (return_free(env, string));
}

char	*ext_redir(const char *string)
{
	t_reform	env;

	if (!ext_init(&env, string))
		return (NULL);
	while (string[(env.p_count)] != '\0')
	{
		if (norm_help1(env, string))
			env.quote = 1;
		else if (norm_help2(env, string))
			env.quote = 0;
		if ((env.p_count) >= 1 && is_redir(string[(env.p_count) + 1])
			&& !is_redir(string[(env.p_count)]) && !env.quote)
		{
			env.str[(env.s_count)++] = string[(env.p_count)++];
			env.str[(env.s_count)++] = ' ';
		}
		env.str[(env.s_count)++] = string[(env.p_count)++];
	}
	env.str[(env.s_count)] = '\0';
	free ((void *)string);
	return (env.str);
}

char	*pipes_reformat(char *line)
{
	t_reform	env;

	if (!ext_init(&env, (const char *)line))
		return (NULL);
	while (line[(env.p_count)] != '\0')
	{
		if (norm_help1(env, (const char *)line))
			env.quote = 1;
		else if (norm_help2(env, (const char *)line))
			env.quote = 0;
		if (line[(env.p_count) + 1] == '|' && !env.quote)
		{
			env.str[(env.s_count)++] = line[(env.p_count)++];
			env.str[(env.s_count)++] = ' ';
		}
		if (line[(env.p_count)] == '|' && !env.quote)
		{
			env.str[(env.s_count)++] = line[(env.p_count)++];
			env.str[(env.s_count)++] = ' ';
		}
		env.str[(env.s_count)++] = line[(env.p_count)++];
	}
	env.str[(env.s_count)] = '\0';
	free (line);
	return (env.str);
}
