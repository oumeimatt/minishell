/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 16:13:53 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/06 12:58:16 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char    *pwd_builtin()
{
	char	*buff;
	int		size;
	char	*str;

	size = 100;
	buff = malloc(sizeof(char) * size);
	str =  getcwd(buff, 100);
	// free(buff);
	return (str);
}

void	exec_pwd()
{
	printf("%s\n", pwd_builtin());
}
