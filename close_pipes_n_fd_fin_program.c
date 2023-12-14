/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes_n_fd_fin_program.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:45:56 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/12/14 17:12:37 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(int pipes[], int cnt_pipe, int fd)
{
	int	i;

	i = 0;
	while (i < cnt_pipe)
	{
		close(pipes[i]);
		i++;
	}
	close(fd);
}

void	print_error_n_exit(int which)
{
	if (which == ARGUMENT_ERROR)
		perror("Argument Error");
	else if (which == PIPE_CREATE_ERROR)
		perror("Pipe creation failed");
	else if (which == FORK_ERROR)
		perror("Fork failure");
	else if (which == FILE_ACCESS_ERROR)
		perror("File access permission error");
	else if (which == OPEN_ERROR)
		perror("Open error");
	else if (which == MALLOC_ERROR)
		perror("malloc error");
	else if (which == INVALID_CMD)
		perror("Invalid cmd");
	else if (which == EXECUVE_ERROR)
		perror("Execve error");
	exit(1);
}
