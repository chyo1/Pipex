/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:20:30 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/12/20 17:26:30 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	remove_backslash(char **cmd)
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

int	move_idx(unsigned int idx, const char *str, int *s)
{
	char	check_char;

	if (str[idx] && (str[idx] == '\'' || str[idx] == '"'))
	{
		check_char = str[idx];
		idx++;
	}
	if (s)
		*s = idx;
	while (str[idx] && str[idx] != check_char)
	{
		if (str[idx] == '\\')
			idx++;
		idx++;
	}
	return (idx);
}

int	get_word_cnt(const char *str, char c)
{
	unsigned int	cnt_word;
	unsigned int	idx;

	cnt_word = 0;
	idx = 0;
	while (str[idx])
	{
		if (str[idx] != c && str[idx] != '"' && str[idx] != '\'')
		{
			cnt_word++;
			while (str[idx] && str[idx] != c)
				idx++;
		}
		else if (str[idx] == '"' || str[idx] == '\'')
		{
			cnt_word++;
			idx = (unsigned int)move_idx(idx, str, 0) + 1;
		}
		else
			idx++;
	}
	return (cnt_word);
}
