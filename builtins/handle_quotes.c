#include "builtins.h"

char	*check_quotes(char *line)
{
	int		i;
	char	*quoted;
	char	*tmp;

	quoted = NULL;
	i = 1;
	if (line[1] == '\'')
		return (ft_single_quotes(line));
	else if (line[1] == '"')
		return (ft_double_quotes(line));
	else
	{
		quoted = ft_strdup("=");
		while (line[i] != '\0')
		{
			if (line[i] == '\'')
			{
				tmp = ft_strdup(quoted);
				free_ret(quoted, NULL);
				quoted = ft_strjoin(tmp, ft_single_quotes(line + i));
				free_ret(tmp, NULL);
				break;
			}
			else if (line[i] == '"')
			{
				tmp = ft_strdup(quoted);
				free_ret(quoted, NULL);
				quoted = ft_strjoin(tmp, ft_double_quotes(line + i));
				free_ret(tmp, NULL);
				break;
			}
			else
			{
				tmp = ft_strdup(quoted);
				free_ret(quoted, NULL);
				quoted = ft_charjoin (tmp, line[i++]);
				free_ret(tmp, NULL);
			}
		}
	}
	return (quoted);
}

char	*ft_single_quotes(char *line)
{
	char	*quoted;
	char	*tmp;
	int		i;

	i = 1;
	quoted = ft_strdup("=");
	while (line[i] != '\0')
	{
		if (line[i] == '\'')
			i++;
		if (line[i] != '\0')
		{
			tmp = ft_strdup(quoted);
			free_ret(quoted, NULL);
			quoted = ft_charjoin(tmp, line[i]);
			free_ret(tmp, NULL);
			i++;
		}
	}
	return(quoted);	
}

char	*ft_double_quotes(char *line)
{
	char	*quoted;
	char	*tmp;
	int		i;

	i = 1;
	quoted = ft_strdup("=");
	while (line[i] != '\0')
	{
		if (line[i] == '"')
			i++;
		if (line[i] != '\0')
		{
			tmp = ft_strdup(quoted);
			free_ret(quoted, NULL);
			quoted = ft_charjoin(tmp, line[i]);
			free_ret(tmp, NULL);
			i++;
		}
	}
	return(quoted);
}