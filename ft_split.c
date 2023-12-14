/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:16:20 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/10/14 12:22:55 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static unsigned int	get_word_cnt(const char *str, char c)
{
	unsigned int	cnt_word;
	unsigned int	idx;

	cnt_word = 0;
	idx = 0;
	while (str[idx])
	{
		if (str[idx] != c)
		{
			cnt_word++;
			while (str[idx] && str[idx] != c)
				idx++;
		}
		else
			idx++;
	}
	return (cnt_word);
}

static void	get_wrd(const char *src, char *ans, unsigned int s, unsigned int e)
{
	unsigned int	idx;

	idx = 0;
	while (idx < e - s)
	{
		ans[idx] = src[s + idx];
		idx++;
	}
	ans[idx] = '\0';
}

static int	fill_ans(char **ans, const char *str, char c)
{
	unsigned int	s;
	unsigned int	idx;
	unsigned int	ans_idx;

	idx = 0;
	ans_idx = 0;
	while (str[idx])
	{
		if (str[idx] != c)
		{
			s = idx;
			while (str[idx] && str[idx] != c)
				idx++;
			ans[ans_idx] = (char *)malloc(sizeof(char) * (idx - s + 1));
			if (ans[ans_idx] == NULL)
				print_error_n_exit(MALLOC_ERROR);
			get_wrd(str, ans[ans_idx], s, idx);
			ans_idx++;
		}
		else
			idx++;
	}
	ans[ans_idx] = 0;
	return (-1);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	cnt_word;
	char			**ans;
	int				err_loc;

	cnt_word = get_word_cnt(s, c);
	ans = (char **)malloc(sizeof(char *) * (cnt_word + 1));
	if (ans == NULL)
		print_error_n_exit(MALLOC_ERROR);
	err_loc = fill_ans(ans, s, c);
	return (ans);
}
