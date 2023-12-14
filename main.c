/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:28:07 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/12/14 17:00:42 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	pid_t	w_child_pid;
	pid_t	r_child_pid;
	t_defaults def;

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
}
