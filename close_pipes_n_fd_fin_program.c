/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes_n_fd_fin_program.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:45:56 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/12/15 20:47:09 by hyowchoi         ###   ########.fr       */
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
	char *error_msg;

	error_msg = NULL;
	// char	*buff = "pipex: input: No such file or directory\n";
	if (which == ARGUMENT_ERROR)
	{
		perror("pipex: input:");
		error_msg = strerror(ENOENT);
	}	
		// *buff = "input: No such file or directory";
	else if (which == PIPE_CREATE_ERROR)
		;// perror("Pipe creation failed");
	else if (which == FORK_ERROR)
		;// perror("Fork failure");
	else if (which == FILE_ACCESS_ERROR)
		;// perror("File access permission Error");
	else if (which == OPEN_ERROR)
		;//  perror("command not found: No such file or directory");
	else if (which == MALLOC_ERROR)
		;// perror("malloc Error");
	else if (which == INVALID_CMD)
		;//perror("command not found: No such file or directory");
	else if (which == EXECUVE_ERROR)
		;// perror("Execve Error");
	perror(error_msg);
	exit(1);
}
