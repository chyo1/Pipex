RM=			rm -f
NAME=		push_swap
BONUS_NAME=	checker
CC=			cc
CFLAGS=		-Wall -Wextra -Werror -g
SRCS_MAN=	find_env_path.c ft_split.c ft_str_func.c\
			pipex.c
.PHONY : all clean fclean re

all : $(NAME)

bonus : $(BONUS_NAME)

$(NAME) : $(SRCS_MAN)
	$(CC) $(CFLAGS) $(SRCS_MAN) -o $(NAME)

$(BONUS_NAME) : $(SRCS_BONUS)
	$(CC) $(CFLAGS) $(SRCS_BONUS) -o $(BONUS_NAME)

clean :

fclean :
	$(RM) $(NAME)
	$(RM) $(BONUS_NAME)

re :
	make fclean
	make all