/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:28:07 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/12/20 14:16:48 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void asd(void)
{
	system("leaks pipex");
}

int	main(int argc, char **argv, char **env)
{
	pid_t		child_pid;
	t_defaults	def;
	int			status;
	int			value;
	int			i;
	int			*pipes;

	atexit(asd);
	if (argc < 5)
		print_error_n_exit(ARGUMENT_ERROR);
	pipes = make_struct_n_pipe(&def, argc, argv, env);
	i = 0;
	while (i < argc - 4)
	{
		if (pipe(&pipes[i * 2]) == -1)
			print_error_n_exit(PIPE_CREATE_ERROR);
		i++;
	}
	i = 2;
	while (i < argc - 1)
	{
		child_pid = fork();
		if (child_pid == -1)
			print_error_n_exit(FORK_ERROR);
		if (child_pid == 0)
		{
			// write_child, execute cmd1 & open infile
			if (i == 2)
			{
				if (ft_strcmp(argv[1], "here_doc") == 0)
				{
					here_doc(def, argv[2]);
					i++;
					read_infile(def, "tmp_file", pipes, 3);
				}
				else
					read_infile(def, argv[1], pipes, 2);
			}

			// execute cmd and send to cmd[n + 1]
			else if (i == argc - 2)
				write_to_outfile(def, argv[argc - 1], pipes);

			// read_child, excute cmd[n - 1] & write outfile
			else
				read_n_write_pipes(def, argv[i], pipes, (i - 2) * 2);
		}
		i++;
	}
	close_pipes(pipes, argc - 4, 0);
	i = 0;
	while (i < argc - 3)
	{
		if (wait(&status) == child_pid)
			value = WEXITSTATUS(status);
		i++;
	}
	exit (value);
}
