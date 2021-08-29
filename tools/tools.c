#include "tools.h"

void	destroy_tab(char **tab, int n)
{
	while (tab[n])
	{
		free (tab[n]);
		tab[n] = NULL;
		n++;
	}
	free (tab);
	tab = NULL;
}

int	is_redir(char c)
{
	if (c == '<')
		return (1);
	else if (c == '>')
		return (2);
	else
		return (0);
}

char	*redirection_reformat(const char *string)
{
	char *str;
	int p_count;
	int s_count;
	int quote;

	quote = 0;
	s_count = 0;
	p_count = 0;
	str = (char *)malloc(sizeof(char) * ft_strlen(string) * 10);
	if (!str)
		return (NULL);
    while (string[p_count] != '\0')
    {
        if ((is_dquote(string[p_count]) || is_squote(string[p_count])) && !quote)
            quote = 1;
        else if ((is_dquote(string[p_count]) || is_squote(string[p_count])) && quote)
            quote = 0;
        if (is_redir(string[p_count + 1]) && !is_redir(string[p_count]) && string[p_count] != ' ' && quote == 0)
        {
            str[s_count++] = string[p_count++];
            str[s_count++] = ' ';
        }
        if (is_redir(string[p_count]) && !is_redir(string[p_count + 1]) && quote == 0)
        {
            str[s_count++] = string[p_count++];
            str[s_count++] = ' ';
        }
        if (is_redir(string[p_count]) && !is_redir(string[p_count - 1]) && string[p_count - 1] != ' ')
            str[s_count++] = ' ';
        str[s_count++] = string[p_count++];
        if (is_redir(string[p_count]) && !is_redir(string[p_count + 1]) && !is_redir(string[p_count - 1]))
            str[s_count++] = ' ';
    }
	str[s_count] = '\0';
	free ((void *)string);
	return (str);
}

char	*pipes_reformat(char *line)
{
	char *str;
	int p_count;
	int	s_count;
	int	quote;
	
	quote = 0;
	s_count = 0;
	p_count = 0;
	str = (char *)malloc(sizeof (char) * ft_strlen(line) * 10);
	if (!str)
		return (NULL);
	while (line[p_count] != '\0')
	{
		if ((is_dquote(line[p_count]) || is_squote(line[p_count])) && !quote)
			quote = 1;
		else if ((is_dquote(line[p_count]) || is_squote(line[p_count])) && quote)
			quote = 0;
		if (line[p_count + 1] == '|' && !quote)
		{
			str[s_count++] = line[p_count++];
			str[s_count++] = ' ';
		}
		if (line[p_count] == '|' && !quote)
		{
			str[s_count++] = line[p_count++];
			str[s_count++] = ' ';
		}
		str[s_count++] = line[p_count++];
	}
	str[s_count] = '\0';
	free (line);
	return (str);
}