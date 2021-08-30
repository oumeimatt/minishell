#include "builtins.h"

char	*check_quotes(char *line)
{
	int		i;
	char	*quoted;

	quoted = NULL;
	i = 0;
	if (line[0] == '\'')
		quoted = ft_single_quotes(line);
	else if (line[0] == '"')
		quoted = ft_double_quotes(line);
	else
	{
		quoted = ft_strdup("");
		while (line[i] != '\0')
		{
			if (line[i] == '\'')
			{
				quoted = ft_strjoin(quoted, ft_single_quotes(line + i));
				break;
			}
			else if (line[i] == '"')
			{
				quoted = ft_strjoin(quoted, ft_double_quotes(line + i));
				break;
			}
			else
				quoted = ft_charjoin(quoted, line[i++]);
		}
	}
	return (quoted);
}

char	*ft_single_quotes(char *line)
{
	char	*quoted;
	int		i;

	i = 0;
	quoted = ft_strdup("");
	while (line[i] != '\0')
	{
		if (line[i] == '\'')
			i++;
		if (line[i] != '\0')
		{
			quoted = ft_charjoin(quoted, line[i]);
			i++;
		}
	}
	return(quoted);	
}

char	*ft_double_quotes(char *line)
{
	char	*quoted;
	int		i;

	i = 0;
	quoted = ft_strdup("");
	while (line[i] != '\0')
	{
		if (line[i] == '"')
			i++;
		if (line[i] != '\0')
		{
			quoted = ft_charjoin(quoted, line[i]);
			i++;
		}
	}
	return(quoted);	
}