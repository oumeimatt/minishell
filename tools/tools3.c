#include "tools.h"

char	*dquotes_reformat(char *line)
{	
	int i;
	int j;
	char *str;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * ft_strlen(line));
	while (line[i] != '\0')
	{
		if (is_dquote(line[i]) && is_dquote(line[i + 1]))
			i += 2;
		str[j++] = line[i++];	
	}
	str[j] = '\0';
	return (str);
}

char		*spaces_dquotes_reformat(char *line)
{
	int	i;
	int dquote;
	int j;
	char *str;

	i = 0;
	j = 0;	
	dquote = 0;
	str = (char *)malloc(sizeof(char) * ft_strlen(line) * 2);
	if (!str)
		return (0);
	while (line[i] != '\0')
	{
		if (is_dquote(line[i]))
			dquote++;
		if (dquote == 2)
		{
			str[j++] = line[i++];
			str[j++] = ' ';
			dquote = 0;
		}
		str[j++] = line[i++];
	}
	str[j] = '\0';
	return (str);
}

char	*spaces_dquotes_reformat2(char *line)
{
	int	i;
	int dquote;
	int j;
	char *str;

	i = 0;
	j = 0;	
	dquote = 0;
	str = (char *)malloc(sizeof(char) * ft_strlen(line) * 2);
	if (!str)
		return (0);
	while (line[i] != '\0')
	{
		if (is_dquote(line[i]))
			dquote++;
		if (dquote == 3)
		{
			str[j++] = ' ';
			str[j++] = line[i++];
			dquote = 1;
		}
		str[j++] = line[i++];
	}
	str[j] = '\0';
	return (str);
}

char	*quotes_reformat(char *line)
{
	int		p_count;
	int		s_count;
	int		d_quote;
	int		s_quote;
	char	*string;

	d_quote = 0;
	s_quote = 0;
	p_count = 0;
	s_count = 0;
	string = (char *)malloc(sizeof(char) * ( ft_strlen(line) + 1));
	if (!string)
		return (NULL);
	while (line[p_count] != '\0')
	{
		if (is_dquote(line[p_count]) && !d_quote && !s_quote && p_count++)
			d_quote = 1;
		else if (is_dquote(line[p_count]) && d_quote)
			d_quote = 0;
		if (is_squote(line[p_count]) && !s_quote && !d_quote && p_count++)
			s_quote = 1;
		else if (is_squote(line[p_count]) && s_quote)
			s_quote = 0;
		if (line[p_count] && (!is_squote(line[p_count] || !is_dquote(line[p_count]))))
			string[s_count++] = line[p_count++];
		if (is_squote(line[p_count]) || is_dquote(line[p_count]))
			continue;
	}
	if (string[s_count - 1] == '\'')
		string[s_count - 1] = 0;
	string[s_count] = 0;
	free (line);
	return (string);
}