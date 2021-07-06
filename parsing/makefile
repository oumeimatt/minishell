QUIET = @

cc = clang

NAME = minishell

SRCS =	srcs/libft/ft_atoi.c\
		srcs/libft/ft_bzero.c\
		srcs/libft/ft_calloc.c\
		srcs/libft/ft_isalnum.c\
		srcs/libft/ft_isalpha.c\
		srcs/libft/ft_isascii.c\
		srcs/libft/ft_isdigit.c\
		srcs/libft/ft_isprint.c\
		srcs/libft/ft_itoa.c\
		srcs/libft/ft_memccpy.c\
		srcs/libft/ft_memchr.c\
		srcs/libft/ft_memcmp.c\
		srcs/libft/ft_memcpy.c\
		srcs/libft/ft_memmove.c\
		srcs/libft/ft_memset.c\
		srcs/libft/ft_putchar_fd.c\
		srcs/libft/ft_putendl_fd.c\
		srcs/libft/ft_putnbr_fd.c\
		srcs/libft/ft_putstr_fd.c\
		srcs/libft/ft_strchr.c\
		srcs/libft/ft_strdup.c\
		srcs/libft/ft_strjoin.c\
		srcs/libft/ft_strlcat.c\
		srcs/libft/ft_strlcpy.c\
		srcs/libft/ft_strlen.c\
		srcs/libft/ft_strmapi.c\
		srcs/libft/ft_strncmp.c\
		srcs/libft/ft_strnstr.c\
		srcs/libft/ft_strrchr.c\
		srcs/libft/ft_strtrim.c\
		srcs/libft/ft_substr.c\
		srcs/libft/ft_tolower.c\
		srcs/libft/ft_toupper.c\
		srcs/libft/ft_split.c\
		srcs/parser/mosdef.c\
		srcs/parser/parser.c\
		srcs/parser/utils.c\
		srcs/parser/cmd.c\
		srcs/parser/tab_utils.c\
		srcs/main.c\
		../execution/builtins/*.c \



INCLUDES =	inc/libft.h\
			inc/minishell.h\

FLAGS = -Wall -Werror -Wextra -lreadline -g -fsanitize=address

all:		$(NAME)

$(NAME):	$(SRCS)
		@echo "Program : $(NAME)"
		@echo "Compiling..."
		$(QUIET)$(cc) -g $(FLAGS) $(SRCS)-I $(INCLUDES)
		@echo "Done."

clean:
			@rm -rf *.o

fclean: clean
			@rm -rf $(NAME)
			@rm -rf ./inc/*.gch
			@rm -rf a.out

re:		fclean all

.PHONY : all clean fclean re