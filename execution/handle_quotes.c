#include "../inc/minishell.h"

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
	int		quote_found;

	i = 0;
	quoted = ft_strdup("");
	while (line[i] != '\0')
	{
		if (line[i] == '\'')
		{
			quoted = ft_charjoin(quoted, line[++i]);
			quote_found = 1;
		}
		else
		{
			if (quote_found == 1)
				i++;
			quoted = ft_charjoin(quoted, line[i]);
			i++;
			quote_found = 0;
		}
	}
	return(quoted);	
}

char	*ft_double_quotes(char *line)
{
	char	*quoted;
	int		i;
	int		quote_found;

	i = 0;
	quoted = ft_strdup("");
	while (line[i] != '\0')
	{
		if (line[i] == '"')
		{
			quoted = ft_charjoin(quoted, line[++i]);
			quote_found = 1;
		}
		else
		{
			if (quote_found == 1)
				i++;
			quoted = ft_charjoin(quoted, line[i]);
			i++;
			quote_found = 0;
		}
	}
	return(quoted);	
}