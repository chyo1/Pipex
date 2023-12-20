/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:00:12 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/12/20 14:10:26 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	remove_backslash(char **cmd)
{
	char	*tmp;
	char	*buf;
	int		idx;
	int		idx_buf;

	tmp = *cmd;
	idx_buf = 0;
	idx = 0;
	while (*tmp != 0)
		if (*tmp++ == '\\')
			idx++;
	buf = (char *)malloc(ft_strlen(*cmd) - idx + 1);
	tmp = *cmd;
	idx = 0;
	while (*(tmp + idx) != 0)
	{
		if (*(tmp + idx) == '\\')
			idx++;
		else
			buf[idx_buf++] = tmp[idx++];
	}
	buf[idx_buf] = 0;
	free(*cmd);
	*cmd = buf;
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
	path = find_n_make_path(def.env_list, cmd[0]);
	execve(path, cmd, def.env);
	print_error_n_exit(EXECUVE_ERROR);
	if (access(cmd[0], X_OK) != 0)
		exit(126);
	exit(1);
}

void	here_doc(t_defaults def, char *limiter)
{
	char	*arg_cmd;
	int		tmpfile_fd;
	char	*tmp;
	char 	*lim;

	arg_cmd = def.argv[2];
	tmpfile_fd = open("tmp_file", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (tmpfile_fd == -1)
		print_error_n_exit(OPEN_ERROR);
	lim = malloc(ft_strlen(limiter) + 3);
	ft_strlcpy(lim, limiter, ft_strlen(limiter) + 1);
	lim[ft_strlen(limiter)] = '\n';
	lim[ft_strlen(limiter) + 1] = '\0'; 
	while (1)
	{
		tmp = get_next_line(0);
		if (strcmp(tmp, lim) == 0)
			break;
		write(tmpfile_fd, tmp, ft_strlen(tmp));
	}
	free(tmp); //
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
	path = find_n_make_path(def.env_list, cmd[0]);
	execve(path, cmd, def.env);
	print_error_n_exit(EXECUVE_ERROR);
	if (access(cmd[0], X_OK) != 0)
		exit(126);
	exit(1);
}

void	write_to_outfile(t_defaults def, char *outfile, int *pipes)
{
	int 	outfile_fd;
	char	*arg_cmd;
	char	*path;
	char	**cmd;
	int		i;

	arg_cmd = def.argv[def.argc - 2];
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
	path = find_n_make_path(def.env_list, cmd[0]);
	execve(path, cmd, def.env);
	print_error_n_exit(EXECUVE_ERROR);
	if (access(cmd[0], X_OK) != 0)
		exit(126);
	exit(1);
}
