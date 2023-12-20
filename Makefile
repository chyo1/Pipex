RM=			rm -f
NAME=		pipex
CC=			cc
CFLAGS=		-Wall -Wextra -Werror -g
SRCS_MAN=	find_env_path.c ft_split.c ft_str_func.c\
			main.c close_pipes_n_fd_fin_program.c do_child.c\
			_get_next_line.c _get_next_line_utils.c parsing.c
SRCS_BONUS= find_env_path.c ft_split.c ft_str_func.c\
			bonus_main.c close_pipes_n_fd_fin_program.c do_child.c\
			_get_next_line.c _get_next_line_utils.c parsing.c
.PHONY : all bonus clean fclean re

all : $(NAME)

$(NAME) : $(SRCS_MAN)
	$(CC) $(CFLAGS) $(SRCS_MAN) -o $(NAME)

bonus : LAST_BONUS

LAST_BONUS : $(SRCS_BONUS)
	$(CC) $(CFLAGS) $(SRCS_BONUS) -o $(NAME)
	touch LAST_BONUS

clean :
	rm LAST_BONUS

fclean :
	make clean
	$(RM) $(NAME)

re :
	make fclean
	make all