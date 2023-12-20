/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:28:07 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/12/20 17:49:32 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	pid_t		last_child_pid;
	t_defaults	def;
	int			status;
	int			value;
	int			i;

	if (argc != 5)
		print_error_n_exit(ARGUMENT_ERROR);
	make_struct_n_pipe(&def, argc, argv, env);
	last_child_pid = do_child(def, argv[1], 2);
	close_pipes(def.pipes, 1, 0);
	i = 0;
	while (i < 2)
	{
		if (wait(&status) == last_child_pid)
			value = WEXITSTATUS(status);
		i++;
	}
	exit (value);
}
