/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:28:07 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/12/27 12:34:53 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	fin_child_process(t_defaults def, int end, int last_child_pid)
{
	int	i;
	int	status;
	int	value;

	// if here_doc, child_cnt is 1 small (argc cnt is 1 large)
	if (ft_strcmp(def.argv[1], "here_doc") == 0)
		end--;
	i = 0;
	while (i < end)
	{
		if (wait(&status) == last_child_pid)
			value = WEXITSTATUS(status);
		i++;
	}
	return (value);
}

int	main(int argc, char **argv, char **env)
{
	pid_t		last_child_pid;
	t_defaults	def;
	int			value;
	char		*file_name;

	if (argc < 5)
		print_error_n_exit(ARGUMENT_ERROR);
	make_struct_n_pipe(&def, argc, argv, env);

	if (ft_strcmp(def.argv[1], "here_doc") == 0)
	{
		file_name = make_file_name("heredoc_tmp_file");
		last_child_pid = do_child(def, file_name, 3);
	}
	else
		last_child_pid = do_child(def, argv[1], 2);

	close_pipes(def.pipes, def.cnt_pipes, 0);

	// find last_child's return code
	value = fin_child_process(def, argc - 3, last_child_pid);

	// remove tmp file
	if (ft_strcmp(def.argv[1], "here_doc") == 0)
		unlink(file_name);
	exit (value);
}
