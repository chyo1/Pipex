/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:00:51 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/12/13 20:28:18 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20000
# endif

#include <unistd.h> // pipe
#include <stdlib.h> // exit
#include <stdio.h> // perror, strerror
#include <fcntl.h> // open, close

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
char	**div_env_path(char **env);
char	*find_n_make_path(char **envp, char *cmd);

#endif
