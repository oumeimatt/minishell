#include "parser.h"

int			is_line(char *line)
{
	if (line && *line)
		add_history(line);
	if (line && !line[0])
	{	
		free (line);
		return (0);
	}
	return (1);
}

char	*reformat_line(t_wrapper *wrp, char *line)
{
	int	flag;

	flag = 0;
	if (ft_strncmp(line, "export", 6))
		flag = check_line_syntax(line);
	else if (!ft_strncmp(line, "export", 6))
		flag = export_check_quotes(line);
	if (flag <= 0)
	{
		load_msg_err(wrp, flag);
		free(line);
		line = NULL;
		return (NULL);
	}
	line = redirection_reformat(line);
	line = pipes_reformat(line);
	line = expand_exit_code(line);
	line = expand_env(wrp, line);
	line = ft_strtrim(line, "\t ");
	return (line);
}

char *expand_env(t_wrapper *wrp, char *string)
{
	int p_count;
	int s_count;
	char *str;
	char *value;
	int c_count;
	int s_flag;
	int d_flag;

	s_flag = 0;
	d_flag = 0;
	p_count = 0;
	s_count = 0;
	str = (char *)malloc(sizeof(char) * ft_strlen(string) * 200);//yes nasty
	if (!str)
		return (NULL);
	while (string[p_count] != '\0')
	{
		if (is_dquote(string[p_count]) && !d_flag)
			d_flag = 1;
		else if (is_dquote(string[p_count] && d_flag))
			d_flag = 0;
		if (string[p_count] == '\'' && !s_flag)
			s_flag = 1;
		else if (string[p_count] == '\'' && s_flag)
			s_flag = 0;
		if (is_dollar(string[p_count]) && !dollar_valid(string[p_count + 1]) && !s_flag)
		{
			p_count++;
			char *ss = ft_substr(string, p_count, get_len_env(&string[p_count]));
			value = get_value_env(wrp->env, ss) + ft_strlen(ss) + 1;
			free (ss);
			p_count += get_len_env(&string[p_count]);
			c_count = 0;
			while (value && value[c_count] != '\0')
				str[s_count++] = value[c_count++];
			if (is_dquote(string[p_count]) || is_squote(string[p_count]))
				continue;
		}
		if (string[p_count])
			if (string[p_count] != '$'|| (is_dollar(string[p_count]) && dollar_valid(string[p_count + 1])) || (is_dollar(string[p_count]) && s_flag))
				str[s_count++] = string[p_count++];
	}
	str[s_count] = '\0';
	free (string);
	return (str);
}

