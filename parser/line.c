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
//	printf ("flag : %d\n", flag);
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
	int		*dq;
	int		*sq;
	char	*str;
	int		s_count;
	int		p_count;
	char	*key;
	char	*value;
	int		j;

	str = malloc(sizeof(char) * ft_strlen(string) * 400);
	if (!str)
		return (NULL);
	p_count = 0;
	s_count = 0;
	dq = ext_dsqmsk(string, 1);
	sq = ext_dsqmsk(string, 0);
	while (string[s_count])
	{
		if (is_dollar(string[s_count]) && !dollar_valid(string[s_count + 1]) && sq[s_count] == 0)
		{
			s_count++;
			key = ft_substr(string, s_count, get_len_env(&string[s_count]));
			if (!get_value_env(&wrp->env, key))
				return (NULL);
			value = get_value_env(&wrp->env, key) + 1;
			free (key);
			s_count += get_len_env(&string[s_count]);
			j = 0;
			while (value && value[j] != '\0')
				str[p_count++] = value[j++];

		}
		if (is_dollar(string[s_count]))
			continue ;
		if (string[s_count])
			str[p_count++] = string[s_count++];
	}
	str[p_count] = '\0';
	free (string);
	free (dq);
	free (sq);
	return (str);
}
