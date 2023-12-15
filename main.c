/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:28:07 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/12/15 14:14:19 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	pid_t		w_child_pid;
	pid_t		r_child_pid;
	t_defaults	def;
	int			status;
	int			value;

	fill_default_struct(&def, argc, argv, env);
	if (argc != 5)
		print_error_n_exit(ARGUMENT_ERROR);
	if (pipe(def.pipes) == -1)
		print_error_n_exit(PIPE_CREATE_ERROR);
	w_child_pid = fork();
	if (w_child_pid == -1)
		print_error_n_exit(FORK_ERROR);
	else if (w_child_pid == 0) // write_child, execute cmd1 & open
		read_infile(def);
	else // parent
	{
		r_child_pid = fork();
		if (r_child_pid == -1)
			print_error_n_exit(FORK_ERROR);
		else if (r_child_pid == 0) // read_child, execute cmd2 & outfile
			write_to_outfile(def);
	}
	close(def.pipes[0]);
	close(def.pipes[1]);
	int i = 0;
	while(i < 2)
	{
		if (wait(&status) == r_child_pid)
			value = WEXITSTATUS(status);
		
		i++;
	}
	exit (value);
}
