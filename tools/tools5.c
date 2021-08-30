#include "tools.h"

void			tab_trimmer(char **tab)
{
	int 	i;

	i = 0;
	while (tab[i])
	{
		tab[i] = ft_strtrim(tab[i], "\"\'");
		i++;
	}		
}

void			debug_tab(char **tab)
{
	int i;
	for (i = 0; tab[i + 1]; i++)
		printf (" [%s] -", tab[i]);
	printf (" [%s]", tab[i]);
}

int			spaces(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}