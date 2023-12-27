/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:00:12 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/12/26 12:41:09 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	do_child(t_defaults def, char *infile, int fir_cmd_loc)
{
	pid_t	child_pid;
	int		i;

	i = 0;
	while (i < 2)
	{
		child_pid = fork();
		if (child_pid == -1)
			print_error_n_exit(FORK_ERROR);
		if (child_pid == 0)
		{
			if (i == 0)
				read_infile(def, infile, def.pipes, fir_cmd_loc);
			else
				write_to_outfile(def, def.argv[def.argc - 1], def.pipes);
		}
		i++;
	}
	return (child_pid);
}

void	read_infile(t_defaults def, char *infile, int *pipes, int fir_cmd_loc)
{
	char	*arg_cmd;
	char	*path;
	char	**cmd;
	int		infile_fd;
	int		i;

	arg_cmd = def.argv[fir_cmd_loc];
	if (access(infile, R_OK) == -1)
		print_error_n_exit(FILE_ACCESS_ERROR);
	infile_fd = open(infile, O_RDONLY);
	if (infile_fd == -1)
		print_error_n_exit(OPEN_ERROR);
	dup2(infile_fd, 0);
	dup2(pipes[1], 1);
	close_pipes(pipes, def.cnt_pipes, infile_fd);
	cmd = ft_split(arg_cmd, ' ');
	i = -1;
	while (cmd[++i] != NULL)
		remove_backslash(&cmd[i]);
	path = find_n_make_path(def.env_list, cmd[0], ft_strlen(cmd[0]));
	execve(path, cmd, def.env);
	print_error_n_exit(EXECUVE_ERROR);
}

void	write_to_outfile(t_defaults def, char *outfile, int *pipes)
{
	int		outfile_fd;
	char	*arg_cmd;
	char	*path;
	char	**cmd;
	int		i;

	arg_cmd = def.argv[3];
	outfile_fd = open(outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
		print_error_n_exit(OPEN_ERROR);
	dup2(pipes[0], 0);
	dup2(outfile_fd, 1);
	close_pipes(pipes, def.cnt_pipes, outfile_fd);
	cmd = ft_split(arg_cmd, ' ');
	i = -1;
	while (cmd[++i] != NULL)
		remove_backslash(&cmd[i]);
	path = find_n_make_path(def.env_list, cmd[0], ft_strlen(cmd[0]));
	execve(path, cmd, def.env);
	print_error_n_exit(EXECUVE_ERROR);
}
