/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:08:07 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/12/13 20:27:46 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**div_env_path(char **env)
{
	const char		cmp[5] = "PATH=";
	unsigned int	i;
	unsigned int	j;
	char			**str;

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
	str = ft_split(env[i], ':');
	// if (str == NULL)
	// {
	// 	perror("malloc error");
	// 	exit(1);
	// }
	return (str);
}

char	*find_n_make_path(char **envp, char *cmd)
{
	unsigned int	i;
	char			*str;
	size_t			cmd_len;

	i = 0;
	cmd_len = ft_strlen(cmd);
	while (envp[i] != NULL)
	{
		str = (char *)malloc(ft_strlen(envp[i]) + cmd_len + 2);
		if (str == NULL)
		{
			perror("malloc error");
			exit(1);
		}
		ft_strlcpy(str, envp[i], ft_strlen(envp[i]) + cmd_len + 2); // path/cmd
		ft_strlcat(str, "/", ft_strlen(envp[i]) + cmd_len + 2);
		ft_strlcat(envp[i], cmd, ft_strlen(envp[i]) + cmd_len + 2);
		if (access((const char *)str, F_OK))
			return (str);
		free(str); // have to free?
		i++;
	}
	// cmd error
	perror("Invalid cmd");
		exit(1);
}
