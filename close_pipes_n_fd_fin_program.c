/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes_n_fd_fin_program.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:45:56 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/12/18 17:11:43 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(int *pipes, int cnt_pipe, int fd)
{
	int	i;

	i = 0;
	while (i < cnt_pipe * 2)
	{
		close(pipes[i]);
		i++;
	}
	if (fd != 0)
		close(fd);
}

void	print_error_n_exit(int which)
{
	if (which == ARGUMENT_ERROR)
		;// write(2, "pipex: input: No such file or directory\n", 40);
	else if (which == PIPE_CREATE_ERROR)
		;// perror("Pipe creation failed");
	else if (which == FORK_ERROR)
		;// perror("Fork failure");
	else if (which == FILE_ACCESS_ERROR || which == OPEN_ERROR)
		write(2, "pipex: input: No such file or directory\n", 40);
	else if (which == MALLOC_ERROR)
		;// perror("malloc Error");
	else if (which == INVALID_CMD)
		;//perror("command not found: No such file or directory");
	else if (which == EXECUVE_ERROR)
		exit(126);
	exit(1);
}
