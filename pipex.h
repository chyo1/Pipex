/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:00:51 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/12/15 20:45:37 by hyowchoi         ###   ########.fr       */
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
	int		pipes[2];
	int		argc;
	char	**argv;
	char	*infile;
	char	*outfile;
}	t_defaults;

#define ARGUMENT_ERROR 0
#define PIPE_CREATE_ERROR 1
#define FORK_ERROR 2
#define FILE_ACCESS_ERROR 3
#define OPEN_ERROR 4
#define MALLOC_ERROR 5
#define INVALID_CMD 6
#define EXECUVE_ERROR 7

#define TRUE 1
#define FALSE 0

// main.c
int	main(int argc, char **argv, char **env);

// ft_split.c
char	**ft_split(char const *s, char c);

// ft_strdup.c
size_t	ft_strlen(const char *s);
char	*ft_strdup(char *s1);
size_t	ft_strlcpy(char *dst, char *src, size_t detsize);
size_t	ft_strlcat(char *dst, char *src, size_t size);

// find_env_path.c
void	fill_default_struct(t_defaults *def, int argc, char **argv, char **env);
char	**div_env_path(char **env);
char	*find_n_make_path(char **envp, char *cmd);

// close_pipes_n_fd_fin_program.c
void	close_pipes(int pipes[], int cnt_pipe, int fd);
void	print_error_n_exit(int which_error);

// do_child.c
void	read_infile(t_defaults def);
void	write_to_outfile(t_defaults def);

#endif
