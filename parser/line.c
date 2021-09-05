/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 13:49:36 by ztaouil           #+#    #+#             */
/*   Updated: 2021/09/05 16:41:28 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	ext_construct(char *string, t_venv *venv)
{
	venv->str = malloc(sizeof(char) * ft_strlen(string) * 400);
	if (!venv->str)
		return (0);
	venv->p_count = 0;
	venv->s_count = 0;
	venv->dq = ext_dsqmsk(string, 1);
	venv->sq = ext_dsqmsk(string, 0);
	return (1);
}

static char	*free_return(t_venv venv, char *string)
{
	venv.str[venv.p_count] = '\0';
	free (string);
	free (venv.dq);
	free (venv.sq);
	return (venv.str);
}

static int	ext_env(t_venv venv, char *string)
{
	if (is_dollar(string[venv.s_count])
		&& !dollar_valid(string[venv.s_count + 1])
		&& venv.sq[venv.s_count] == 0)
		return (1);
	return (0);
}

static char	*ext_norm(t_venv venv, char *string)
{
	return (ft_substr(string, venv.s_count,
			get_len_env(&string[venv.s_count])));
}

char	*expand_env(t_wrapper *wrp, char *string)
{
	t_venv	venv;

	if (!ext_construct(string, &venv))
		return (NULL);
	while (string[venv.s_count])
	{
		if (ext_env(venv, string))
		{
			venv.s_count++;
			venv.key = ext_norm(venv, string);
			if (!get_value_env(&wrp->env, venv.key))
				break ;
			venv.value = get_value_env(&wrp->env, venv.key) + 1;
			free (venv.key);
			venv.s_count += get_len_env(&string[venv.s_count]);
			venv.j = 0;
			while (venv.value && venv.value[venv.j] != '\0')
				venv.str[venv.p_count++] = venv.value[venv.j++];
		}
		if (ext_env_exp(venv, string))
			continue ;
		if (string[venv.s_count])
			venv.str[venv.p_count++] = string[venv.s_count++];
	}
	return (free_return(venv, string));
}
