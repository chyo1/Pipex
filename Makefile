RM=			rm -f
NAME=		pipex
CC=			cc
CFLAGS=		-Wall -Wextra -Werror -g
SRCS_MAN=	main.c\
			find_env_path.c do_child.c\
			ft_split.c ft_str_func.c parsing.c\
			close_pipes_n_fd_fin_program.c\
			_get_next_line.c _get_next_line_utils.c
SRCS_BONUS= main_bonus.c\
			find_env_path_bonus.c do_child_bonus.c\
			ft_split.c ft_str_func.c parsing.c\
			close_pipes_n_fd_fin_program.c\
			_get_next_line.c _get_next_line_utils.c\
			make_file_name.c
.PHONY : all bonus clean fclean re

all : $(NAME)

$(NAME) : LAST_ALL

LAST_ALL : $(SRCS_MAN)
	$(CC) $(CFLAGS) $(SRCS_MAN) -o $(NAME)
	touch LAST_ALL

bonus : LAST_BONUS

LAST_BONUS : $(SRCS_BONUS)
	$(CC) $(CFLAGS) $(SRCS_BONUS) -o $(NAME)
	touch LAST_BONUS

clean :
	rm LAST_ALL
	rm LAST_BONUS

fclean :
	make clean
	$(RM) $(NAME)

re :
	make fclean
	make all