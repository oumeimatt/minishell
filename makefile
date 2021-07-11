QUIET = @

cc = clang

NAME = minishell

SRCS =	parsing/libft/ft_atoi.c\
		parsing/libft/ft_bzero.c\
		parsing/libft/ft_calloc.c\
		parsing/libft/ft_isalnum.c\
		parsing/libft/ft_isalpha.c\
		parsing/libft/ft_isascii.c\
		parsing/libft/ft_isdigit.c\
		parsing/libft/ft_isprint.c\
		parsing/libft/ft_itoa.c\
		parsing/libft/ft_memccpy.c\
		parsing/libft/ft_memchr.c\
		parsing/libft/ft_memcmp.c\
		parsing/libft/ft_memcpy.c\
		parsing/libft/ft_memmove.c\
		parsing/libft/ft_memset.c\
		parsing/libft/ft_putchar_fd.c\
		parsing/libft/ft_putendl_fd.c\
		parsing/libft/ft_putnbr_fd.c\
		parsing/libft/ft_putstr_fd.c\
		parsing/libft/ft_strchr.c\
		parsing/libft/ft_strdup.c\
		parsing/libft/ft_strjoin.c\
		parsing/libft/ft_strlcat.c\
		parsing/libft/ft_strlcpy.c\
		parsing/libft/ft_strlen.c\
		parsing/libft/ft_strmapi.c\
		parsing/libft/ft_strncmp.c\
		parsing/libft/ft_strnstr.c\
		parsing/libft/ft_strrchr.c\
		parsing/libft/ft_strtrim.c\
		parsing/libft/ft_substr.c\
		parsing/libft/ft_tolower.c\
		parsing/libft/ft_toupper.c\
		parsing/libft/ft_split.c\
		parsing/libft/ft_split2.c\
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
		parsing/main.c\
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

FLAGS = -Wall -Werror -Wextra -lreadline -g #-fsanitize=address

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