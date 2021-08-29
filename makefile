CC = clang

NAME = minishell

SRCS =		libft/ft_atoi.c\
		libft/ft_bzero.c\
		libft/ft_calloc.c\
		libft/ft_isalnum.c\
		libft/ft_isalpha.c\
		libft/ft_isascii.c\
		libft/ft_isdigit.c\
		libft/ft_isprint.c\
		libft/ft_itoa.c\
		libft/ft_memccpy.c\
		libft/ft_memchr.c\
		libft/ft_memcmp.c\
		libft/ft_memcpy.c\
		libft/ft_memmove.c\
		libft/ft_memset.c\
		libft/ft_putchar_fd.c\
		libft/ft_putendl_fd.c\
		libft/ft_putnbr_fd.c\
		libft/ft_putstr_fd.c\
		libft/ft_strchr.c\
		libft/ft_strdup.c\
		libft/ft_strjoin.c\
		libft/ft_strlcat.c\
		libft/ft_strlcpy.c\
		libft/ft_strlen.c\
		libft/ft_strmapi.c\
		libft/ft_strncmp.c\
		libft/ft_strcmp.c\
		libft/ft_strnstr.c\
		libft/ft_strrchr.c\
		libft/ft_strtrim.c\
		libft/ft_substr.c\
		libft/ft_tolower.c\
		libft/ft_toupper.c\
		libft/ft_split.c\
		libft/ft_split2.c\
		\
		execution/execution.c\
		execution/ft_exec_cmd.c\
		execution/get_path.c\
		execution/ft_cmd_redir.c\
		execution/ft_redirection.c\
		execution/ft_here_doc.c\
		execution/ft_pipes_loop.c\
		\
		builtins/cd_builtin.c\
		builtins/echo_builtin.c\
		builtins/env_builtin.c\
		builtins/exit_builtin.c\
		builtins/export_builtin.c\
		builtins/is_builtin.c\
		builtins/pwd_builtin.c\
		builtins/unset_builtin.c\
		builtins/handle_quotes.c\
		builtins/utils.c\
		builtins/split.c\
		\
		define/debugg.c\
		define/define.c\
		define/destroy.c\
		define/ldestroy.c\
		\
		list/list.c\
		\
		parser/err.c\
		parser/line.c\
		parser/line2.c\
		parser/parser.c\
		parser/tokens.c\
		parser/wrapper.c\
		\
		petitshell/petitshell.c\
		\
		tools/tools.c\
		tools/tools2.c\
		tools/tools3.c\
		tools/tools4.c\
		tools/tools5.c\
		\
		signals/signal.c\
		\

FLAGS = -Wall -Werror -Wextra -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include -fsanitize=address

all:		$(NAME)

$(NAME):	$(SRCS)
		@echo "Compiling..."
		@$(CC) $(FLAGS) -o $(NAME) $(SRCS)
		@echo "Done."

clean:
			@rm -rf *.o
			@rm -rf ./inc/*.gch
			
fclean: clean
			@rm -rf $(NAME)

re:		fclean all

.PHONY : all clean fclean re