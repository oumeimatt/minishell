/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 08:43:27 by ztaouil           #+#    #+#             */
/*   Updated: 2021/09/04 14:44:29 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

int	*ext_dsqmsk(const char *str, int flag)
{
	t_dsqmk	env;

	env.msk = malloc(sizeof(int) * strlen(str));
	env.dquote = 0;
	env.squote = 0;
	env.i = 0;
	while (str[env.i])
	{
		if (is_dquote(str[env.i]) && env.dquote)
			env.dquote = 0;
		else if (is_squote(str[env.i]) && env.squote)
			env.squote = 0;
		else if (is_dquote(str[env.i]) && !env.squote)
			env.dquote = 1;
		else if (is_squote(str[env.i]) && !env.dquote)
			env.squote = 1;
		if (flag)
			env.msk[env.i] = env.dquote;
		else
			env.msk[env.i] = env.squote;
		(env.i)++;
	}
	return (env.msk);
}

int	*dsqmsk(const char *str)
{
	int		*dmsk;
	int		*smsk;
	int		*msk;
	int		i;

	dmsk = ext_dsqmsk(str, 1);
	smsk = ext_dsqmsk(str, 0);
	msk = malloc(sizeof(int) * strlen(str));
	i = 0;
	while (str[i] != '\0')
	{
		if (is_squote(str[i]) && dmsk[i] == 0)
			msk[i] = 1;
		else if (is_dquote(str[i]) && smsk[i] == 0)
			msk[i] = 1;
		else
			msk[i] = 0;
		i++;
	}
	free (dmsk);
	free (smsk);
	return (msk);
}

int	count_skip(int *qmsk, int i, int len)
{
	int	count;

	count = 0;
	while (i < len)
	{
		if (qmsk[i] == 0)
			break ;
		i++;
		count++;
	}
	return (count);
}

char	*purge_quotes(char *str)
{
	int		s_count;
	int		l_count;
	char	*line;
	int		*qmsk;

	l_count = 0;
	s_count = 0;
	qmsk = dsqmsk((const char *)str);
	line = malloc(sizeof(char) * strlen(str) + 10);
	while (str[s_count])
	{
		if (qmsk[s_count] == 1)
			s_count += count_skip(qmsk, s_count, strlen(str));
		if (str[s_count])
			line[l_count++] = str[s_count++];
	}
	line[l_count] = '\0';
	free (qmsk);
	free (str);
	return (line);
}
