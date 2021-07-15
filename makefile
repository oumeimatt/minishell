QUIET = @

cc = clang

NAME = minishell

SRCS =	libft/ft_atoi.c\
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
		libft/ft_strnstr.c\
		libft/ft_strrchr.c\
		libft/ft_strtrim.c\
		libft/ft_substr.c\
		libft/ft_tolower.c\
		libft/ft_toupper.c\
		libft/ft_split.c\
		libft/ft_split2.c\
		\
		parsing/srcs/mosdef.c\
		parsing/srcs/parser.c\
		parsing/srcs/utils.c\
		parsing/srcs/cmd.c\
		parsing/srcs/tab_utils.c\
		parsing/srcs/line.c\
		parsing/srcs/lstredir.c\
		parsing/srcs/parser2.c\
		parsing/srcs/varenv.c\
		parsing/srcs/error.c\
		parsing/srcs/line2.c\
		parsing/srcs/sighandler.c\
		parsing/main.c\
		\
		execution/builtins/*.c\
		execution/ft_exec_cmd.c\
		execution/get_path.c\
		execution/split.c\
		execution/ft_redirection.c\
		execution/ft_here_doc.c\
		execution/ft_cmd_redir.c\
		execution/ft_pipes_loop.c\



INCLUDES =	inc/libft.h\
			inc/minishell.h\

FLAGS = -g -Wall -Werror -Wextra -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include #-fsanitize=address

all:		$(NAME)

$(NAME):	$(SRCS)
		@echo "Compiling..."
		$(QUIET)$(cc) $(FLAGS) $(SRCS) -I $(INCLUDES) 
		@echo "Done."

clean:
			@rm -rf *.o

fclean: clean
			@rm -rf $(NAME)
			@rm -rf ./inc/*.gch
			@rm -rf a.out

re:		fclean all

.PHONY : all clean fclean re