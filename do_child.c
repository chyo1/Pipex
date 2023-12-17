/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:00:12 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/12/17 19:27:59 by hyowchoi         ###   ########.fr       */
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

void	read_infile(t_defaults def)
{
	char	*arg_cmd;
	char	*path;
	char	**cmd;
	int		infile_fd;

	arg_cmd = def.argv[2];
	if (access(def.infile, R_OK) == -1)
		print_error_n_exit(FILE_ACCESS_ERROR);
	infile_fd = open(def.infile, O_RDONLY);
	if (infile_fd == -1)
		print_error_n_exit(OPEN_ERROR);
	dup2(infile_fd, 0);
	dup2(def.pipes[1], 1);
	close_pipes(def.pipes, 2, infile_fd);
	cmd = ft_split(arg_cmd, ' ');
	int i =0;
	while (cmd[i] != NULL)
	{
		remove_backslash(&cmd[i]);
		i++;
	}
	// printf("cmd1 : %s %s\n", cmd[0], cmd[1]);
	// if (ft_strchr(cmd[0], '/') != 0) //
	// 	exit(1);//
	path = find_n_make_path(def.env_list, cmd[0]);
	execve(path, cmd, def.env);
	print_error_n_exit(EXECUVE_ERROR);
	if (access(cmd[0], X_OK) != 0)
		exit(126);
	exit(1);
}

void	write_to_outfile(t_defaults def)
{
	int 	outfile_fd;
	char	*arg_cmd;
	char	*path;
	char	**cmd;

	arg_cmd = def.argv[def.argc - 2];
	outfile_fd = open(def.outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
		print_error_n_exit(OPEN_ERROR);
	dup2(def.pipes[0], 0);
	dup2(outfile_fd, 1);
	close_pipes(def.pipes, 2, outfile_fd);
	cmd = ft_split(arg_cmd, ' ');
	int i =0;
	while (cmd[i] != NULL)
	{
		remove_backslash(&cmd[i]);
		i++;
	}
	// printf("cmd2 : %s %s\n", cmd[0], cmd[1]);
	// if (ft_strchr(cmd[0], '/') != 0)
	// 	exit(1);//
	path = find_n_make_path(def.env_list, cmd[0]);
	execve(path, cmd, def.env);
	print_error_n_exit(EXECUVE_ERROR);
	if (access(cmd[0], X_OK) != 0)
		exit(126);
	exit(1);
}
