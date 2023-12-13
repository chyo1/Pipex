/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:28:07 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/12/13 20:28:44 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	int		pipes[2];
	pid_t	w_child_pid;
	pid_t	r_child_pid;
	char	**cmd;
	char	**envp;
	char	*path;
	char	buf[BUFFER_SIZE];

	if (argc != 4)
	{
		perror("argument error\n");
		exit(1); //
	}	
	envp = div_env_path(env);
	if (pipe(pipes) == -1)
	{
		perror("Pipe creation failed\n");
		exit(1); //
	}
	dup2(pipes[0], 0);
	dup2(pipes[1], 1);
	w_child_pid = fork();
	if (w_child_pid == -1)
	{
		perror("Fork failure\n");
		exit(1); //
	}
	else if (w_child_pid == 0) // write_child, execute cmd1 & open
	{
		if (access(argv[1], R_OK) == -1)
			{
				perror("File access permission error\n");
				exit(1);
			}
		cmd = ft_split(argv[2], ' ');
		path = find_n_make_path(envp, cmd[0]);
		execve(argv[1], cmd, (char * const *)path);
		perror("execve error\n");
	}
	else // parent
	{
		r_child_pid = fork();
		if (r_child_pid == -1)
		{
			perror("Fork failure\n");
			exit(1); //
		}
		else if (r_child_pid == 0) // read_child, execute cmd2 & outfile
		{
			read(pipes[0], buf, BUFFER_SIZE);
			cmd = ft_split(argv[3], ' ');
			path = find_n_make_path(envp, cmd[0]);
			execve(argv[1], cmd, (char * const *)path);
			perror("execve error\n");
		}
	}
	int outfile_fd = open(argv[4], O_RDWR | O_CREAT, S_IRWXU);
	dup2(outfile_fd, 0);
}
