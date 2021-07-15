/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 13:57:18 by ztaouil           #+#    #+#             */
/*   Updated: 2021/07/15 19:49:56 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		str[s_count++] = string[p_count];
		p_count++;
	}
	str[s_count] = '\0';
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
	str = (char *)malloc (sizeof (char) * ft_strlen(line) * 10);
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
	return (str);
}

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

static void	norme_quotes_reformat(char *line, int *p_count, int *s_quote, int *d_quote)
{
	if (is_dquote(line[*p_count]) && !*d_quote && !*s_quote && (*p_count)++)
		*d_quote = 1;
	else if (is_dquote(line[*p_count]) && *d_quote && (*p_count)++)
		*d_quote = 0;
	if (is_squote(line[*p_count]) && !*d_quote && !*s_quote && ++(*p_count))
		*s_quote = 1;
	else if (is_squote(line[*p_count]) && *s_quote && ++(*p_count))
		*s_quote = 0;
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
	string = (char *)malloc(sizeof(char) * ft_strlen(line));
	if (!string)
		return (NULL);
	while (line[p_count] != '\0')
	{
		norme_quotes_reformat(line, &p_count, &s_quote, &d_quote);
		string[s_count++] = line[p_count++];
	}
	return (string);
}

char	*reformat_line(t_wrapper *wrp, char *line)
{
	int	flag;

	flag = 0;
	line = redirection_reformat(line);
	line = pipes_reformat(line);
	line = expand_exit_code(wrp, line);
	line = expand_env(wrp, line);
	printf("%s\n", line);
	return (line);
	line = ft_strtrim(line, "\t ");
	if (ft_strncmp(line, "export", 6))
		flag = check_line_syntax(line);
	else if (!ft_strncmp(line, "export", 6))
		flag = export_check_quotes(line);
	if (flag <= 0)
	{
		load_msg_err(wrp, flag);
		free(line);
		line = NULL;
	}
	return (line);
}

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
