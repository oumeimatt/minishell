#include "tools.h"

int	export_check_quotes(char *line)
{
	int		i;
	char	tmp;

	tmp = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (is_dquote(line[i]) || is_squote(line[i]))
		{
			tmp = line[i];
			i++;
			while (line[i] != '\0')
			{
				if (tmp == line[i] && (line[i + 1] == '\0' || line[i + 1]
						== ' ' || !is_dquote(line[i + 1]
							|| !is_squote(line[i + 1]))))
					return (1);
				i++;
			}
			return (0);
		}
		i++;
	}
	return (1);
}

int		get_len_env(char *string)
{
	int p_count;

	p_count = 0;
	while (string[p_count] != '\0' && ft_isalnum(string[p_count]))
		p_count++;
	return (p_count);
}

char		*expand_exit_code(char *string)
{
	int i;
	int j;
	char *str;
	int c_count;

	i = 0;
	j = 0;
	c_count = 0;
	str = (char *)malloc(sizeof(char) * ft_strlen(string) * 5);
	if (!str)
		return (NULL);
	while (string[i] != '\0')
	{
		if (is_dollar(string[i]) && string[i + 1] == '?')
		{
			char *tmp = ft_itoa(666);//
			while (tmp[c_count] != '\0')
				str[j++] = tmp[c_count++];
			free (tmp);
			i += 2;
		}
		if (string[i] != '\0')
			str[j++] = string[i++];
	}
	str[j] = '\0';
	free (string);
	return (str);	
}

int  dollar_valid(char c)
{
	if (c == '\'' || c == '"' || c == '\0')
		return (1);
	return (0);
}