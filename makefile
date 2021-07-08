QUIET = @

cc = clang

NAME = minishell

SRCS =	parsing/srcs/libft/ft_atoi.c\
		parsing/srcs/libft/ft_bzero.c\
		parsing/srcs/libft/ft_calloc.c\
		parsing/srcs/libft/ft_isalnum.c\
		parsing/srcs/libft/ft_isalpha.c\
		parsing/srcs/libft/ft_isascii.c\
		parsing/srcs/libft/ft_isdigit.c\
		parsing/srcs/libft/ft_isprint.c\
		parsing/srcs/libft/ft_itoa.c\
		parsing/srcs/libft/ft_memccpy.c\
		parsing/srcs/libft/ft_memchr.c\
		parsing/srcs/libft/ft_memcmp.c\
		parsing/srcs/libft/ft_memcpy.c\
		parsing/srcs/libft/ft_memmove.c\
		parsing/srcs/libft/ft_memset.c\
		parsing/srcs/libft/ft_putchar_fd.c\
		parsing/srcs/libft/ft_putendl_fd.c\
		parsing/srcs/libft/ft_putnbr_fd.c\
		parsing/srcs/libft/ft_putstr_fd.c\
		parsing/srcs/libft/ft_strchr.c\
		parsing/srcs/libft/ft_strdup.c\
		parsing/srcs/libft/ft_strjoin.c\
		parsing/srcs/libft/ft_strlcat.c\
		parsing/srcs/libft/ft_strlcpy.c\
		parsing/srcs/libft/ft_strlen.c\
		parsing/srcs/libft/ft_strmapi.c\
		parsing/srcs/libft/ft_strncmp.c\
		parsing/srcs/libft/ft_strnstr.c\
		parsing/srcs/libft/ft_strrchr.c\
		parsing/srcs/libft/ft_strtrim.c\
		parsing/srcs/libft/ft_substr.c\
		parsing/srcs/libft/ft_tolower.c\
		parsing/srcs/libft/ft_toupper.c\
		parsing/srcs/libft/ft_split.c\
		parsing/srcs/libft/ft_split2.c\
		parsing/srcs/parser/mosdef.c\
		parsing/srcs/parser/parser.c\
		parsing/srcs/parser/utils.c\
		parsing/srcs/parser/cmd.c\
		parsing/srcs/parser/tab_utils.c\
		parsing/srcs/parser/line.c\
		parsing/srcs/parser/lstredir.c\
		parsing/srcs/main.c\
		execution/builtins/*.c\
		execution/ft_exec_cmd.c\
		execution/get_path.c\
		execution/split.c\
		execution/ft_redirection.c\




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