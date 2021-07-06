/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 17:08:13 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/06 15:07:53 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <string.h>



void		debug_tab(char **tab)
{
	int i;
	for (i = 0; tab[i + 1] != NULL; i++)
		printf("[%s] - ", tab[i]);
	if (tab[i] != NULL)
		printf("[%s]\n", tab[i]);
}

int         main(int argc, char **argv, char **envp)
{
	t_wrapper *wrp;

	(void)argc;
	(void)argv;
	wrp = contruct_wrapper();

	parser(wrp, envp);
	return (0);
}


/* 	while (1)
	{
		char *line = readline(">$ ");
		char **tab;
		
		add_history (line);
		tab = ft_split(line, '|');
		debug_tab(tab);
		destroy_tab(tab);
	}
	return 0; */

	
/* 	int 	ip;
	char **tab = (char *[]){ "Hello, World!", "$HOME", "'$LOGNAME'"};
	ip = 0;
	
	printf("%s\n", tab[0]);
	printf("%s\n", tab[1]);
	printf("%s\n", tab[2]);

	printf ("\n\nenv_variable : %d", env_variable(tab, &ip));
	printf ("\nip : %d", ip);
	return 0; */


/* int			main()
{
	charray test;
	char	**split;
	
	test = charray_create(30, 3, '^');
	charray_set(test, 15, 0, '$');
	charray_set(test, 15, 1, '?');
	charray_set(test, 15, 2, '!');
	charray_debug(test);
	
	split = ft_split((const char *)charray_get_line(test, 1), '?');
	debug_tab(split);
	charray spl = charray_create(ft_strlen(split[0]), 3, '-');
	for (int i = 0; i < 2; i++)
		charray_set_line (spl, i, split[i]);
	charray_debug(spl);

	charray_destroy(&test);
	return (0);
} */