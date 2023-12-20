/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:00:51 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/12/20 17:24:36 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20000
# endif

# include <unistd.h> // pipe
# include <stdlib.h> // exit
# include <stdio.h> // perror, strerror
# include <fcntl.h> // open, close
# include <sys/wait.h> // wait, waitpid
# include <errno.h> // strerror
# include <string.h> //?

typedef struct s_defaults
{
	char	**env;
	char	**env_list;
	int		argc;
	char	**argv;
	int		*pipes;
	int		cnt_pipes;

}	t_defaults;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2048
# endif

typedef struct s_list
{
	char			*str;
	int				fd;
	ssize_t			len;
	ssize_t			size;
	ssize_t			loc;
	struct s_list	*next;
}	t_list;

# define ARGUMENT_ERROR 0
# define PIPE_CREATE_ERROR 1
# define FORK_ERROR 2 
# define FILE_ACCESS_ERROR 3
# define OPEN_ERROR 4
# define MALLOC_ERROR 5
# define INVALID_CMD 6
# define EXECUVE_ERROR 7

# define TRUE 1
# define FALSE 0

// main.c
int		main(int argc, char **argv, char **env);

// ft_split.c
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);

// ft_str_func.c
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, char *src, size_t detsize);
size_t	ft_strlcat(char *dst, char *src, size_t size);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(char *s1, char *s2);

// find_env_path.c
int		*make_struct_n_pipe(t_defaults *def, int argc, char **argv, char **env);
char	**div_env_path(char **env);
char	*find_n_make_path(char **envp, char *cmd, size_t cmd_len);

// close_pipes_n_fd_fin_program.c
void	close_pipes(int *pipes, int cnt_pipe, int fd);
void	print_error_n_exit(int which_error);

// do_child.c
int		do_child(t_defaults def, char *infile, int fir_cmd_loc);
void	read_infile(t_defaults def, char *infile, int *pipes, int fir_cmd_loc);
void	here_doc(t_defaults def, char *limiter);
void	write_to_outfile(t_defaults def, char *outfile, int *pipes);
void	read_n_write_pipes(t_defaults def, char *cmd2, int *pipes, int idx);

// parsing.c
void	remove_backslash(char **cmd);
int		move_idx(unsigned int idx, const char *str, int *s);
int		get_word_cnt(const char *str, char c);

// get_next_line.c
char	*get_next_line(int fd);
int		cpy_buff(t_list *node, char *buff, ssize_t cnt);
int		find_endl(t_list *node, ssize_t cnt);
char	*get_ans(t_list **root, t_list *node);

// get_next_line_utils.c
t_list	*find_or_make_lst(t_list **root, int fd);
int		init_node(t_list *node, int fd);
void	ft_lstadd_back(t_list **lst, t_list *new_node);
char	*list_free_and_connect(t_list **lst, int fd);

#endif
