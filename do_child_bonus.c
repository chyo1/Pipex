/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_child_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:00:12 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/12/27 12:27:59 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	do_child(t_defaults def, char *infile, int fir_cmd_loc)
{
	pid_t	child_pid;
	int		i;

	i = 1;
	while (++i < def.argc - 1)
	{
		child_pid = fork();
		if (child_pid == -1)
			print_error_n_exit(FORK_ERROR);
		if (child_pid == 0)
		{
			if (i == 2)
			{
				// here_doc
				if (ft_strcmp(def.argv[1], "here_doc") == 0)
					here_doc(infile, def.argv[i++]);

				// read infile or here_doc file & execute cmd
				read_infile(def, infile, def.pipes, fir_cmd_loc);
			}

			// execute cmd & write to outfile
			else if (i == def.argc - 2)
				write_to_outfile(def, def.argv[def.argc - 1], def.pipes);
			else
				read_n_write_pipes(def, def.argv[i], def.pipes, (i - 2) * 2);
		}
	}
	return (child_pid);
}

void	here_doc(char *file_name, char *limiter)
{
	int		tmpfile_fd;
	char	*tmp;
	char	*lim;

	tmpfile_fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (tmpfile_fd == -1)
		print_error_n_exit(OPEN_ERROR);

	// make lim -> lim\n
	lim = malloc(ft_strlen(limiter) + 3);
	if (lim == NULL)
		print_error_n_exit(MALLOC_ERROR);
	ft_strlcpy(lim, limiter, ft_strlen(limiter) + 1);
	ft_strlcat(lim, "\n", ft_strlen(limiter) + 3);
	while (1)
	{
		tmp = get_next_line(0);
		// if input equals lim, break;
		if (ft_strcmp(tmp, lim) == 0)
			break ;

		// write to tmpfile before input isn't lim
		write(tmpfile_fd, tmp, ft_strlen(tmp));
	}
	free(tmp);
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

	// find cmd path
	path = find_n_make_path(def.env_list, cmd[0], ft_strlen(cmd[0]));
	execve(path, cmd, def.env);
	print_error_n_exit(EXECUVE_ERROR);
}

void	read_n_write_pipes(t_defaults def, char *cmd2, int *pipes, int idx)
{
	char	*path;
	char	**cmd;
	int		i;

	dup2(pipes[idx - 2], 0);
	dup2(pipes[idx + 1], 1);
	close_pipes(pipes, def.cnt_pipes, 0);
	cmd = ft_split(cmd2, ' ');
	i = -1;
	while (cmd[++i] != NULL)
		remove_backslash(&cmd[i]);

	// find cmd path
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

	// open outfile
	arg_cmd = def.argv[def.argc - 2];
	if (ft_strcmp(def.argv[1], "here_doc") == 0)
		outfile_fd = open(outfile, O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		outfile_fd = open(outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
		print_error_n_exit(OPEN_ERROR);

	dup2(pipes[def.cnt_pipes * 2 - 2], 0);
	dup2(outfile_fd, 1);
	close_pipes(pipes, def.cnt_pipes, outfile_fd);

	cmd = ft_split(arg_cmd, ' ');
	i = -1;
	while (cmd[++i] != NULL)
		remove_backslash(&cmd[i]);

	// find cmd path
	path = find_n_make_path(def.env_list, cmd[0], ft_strlen(cmd[0]));
	execve(path, cmd, def.env);
	print_error_n_exit(EXECUVE_ERROR);
}
