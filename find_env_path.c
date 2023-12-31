/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:08:07 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/12/27 12:31:36 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	make_struct_n_pipe(t_defaults *def, int argc, char **argv, char **env)
{
	int	*pipes;

	def->argc = argc;
	def->argv = argv;
	def->env = env;
	def->env_list = div_env_path(env);
	pipes = (int *)malloc(sizeof(int) * 2);
	if (pipes == NULL)
		print_error_n_exit(MALLOC_ERROR);

	// make pipes
	if (pipe(&pipes[0]) == -1)
		print_error_n_exit(PIPE_CREATE_ERROR);
	def->pipes = pipes;
	def->cnt_pipes = 1;
}

// find env_path & cut
char	**div_env_path(char **env)
{
	const char		cmp[5] = "PATH=";
	unsigned int	i;
	unsigned int	j;
	char			**str;
	char			*tmp;

	i = 0;
	while (env[i] != NULL)
	{
		j = 0;
		while (env[i][j] == cmp[j])
			j++;
		if (j == 5)
			break ;
		i++;
	}
	if (env[i] == NULL)
		tmp = "/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:.";
	else
		tmp = env[i] + 5;
	str = ft_split(tmp, ':');
	return (str);
}

char	*find_n_make_path(char **envp, char *cmd, size_t cmd_len)
{
	char			*str;
	unsigned int	i;

	// if cmd has path and is corret -> return cmd
	if (ft_strchr(&cmd[0], '/') != 0 && access((const char *)cmd, F_OK) == 0)
		return (cmd);

	// if cmd has wrong path -> error
	if (ft_strchr(&cmd[0], '/') != 0)
		exit(127);
	i = 0;
	while (envp[i] != NULL)
	{
		str = (char *)malloc(ft_strlen(envp[i]) + cmd_len + 2);
		if (str == NULL)
			print_error_n_exit(MALLOC_ERROR);
		ft_strlcpy(str, envp[i], ft_strlen(envp[i]) + cmd_len + 2);
		ft_strlcat(str, "/", ft_strlen(envp[i]) + cmd_len + 2);
		ft_strlcat(str, cmd, ft_strlen(envp[i]) + cmd_len + 2);

		// if path is right -> return the path
		if (access((const char *)str, F_OK) == 0)
			return (str);
		free(str);
		i++;
	}

	// cannot find cmd path -> invalid cmd
	write(2, "pipex: ", 7);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	exit(127);
}
