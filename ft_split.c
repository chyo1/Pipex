/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:43:18 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/12/20 17:25:54 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

static void	put_ans_idx(char **ans, const char *str, int len, int *ans_idx)
{
	ans[*ans_idx] = (char *)malloc(sizeof(char) * (len));
	if (ans[*ans_idx] == NULL)
		print_error_n_exit(MALLOC_ERROR);
	get_wrd(str, ans[*ans_idx], 0, len - 1);
	(*ans_idx)++;
}

static void	fill_ans(char **ans, const char *str, char c)
{
	int		s;
	int		idx;
	int		ans_idx;

	idx = 0;
	ans_idx = 0;
	while (str[idx])
	{
		if (str[idx] != c && str[idx] != '"' && str[idx] != '\'')
		{
			s = idx;
			while (str[idx] && str[idx] != c)
				idx++;
			put_ans_idx(ans, &str[s], idx - s + 1, &ans_idx);
		}
		else if (str[idx] == '"' || str[idx] == '\'')
		{
			idx = (unsigned int)move_idx(idx, str, &s);
			put_ans_idx(ans, &str[s], idx - s + 1, &ans_idx);
			idx++;
		}
		else
			idx++;
	}
}

char	**ft_split(char const *s, char c)
{
	unsigned int	cnt_word;
	char			**ans;

	cnt_word = (unsigned int)get_word_cnt(s, c);
	ans = (char **)malloc(sizeof(char *) * (cnt_word + 1));
	if (ans == NULL)
		print_error_n_exit(MALLOC_ERROR);
	fill_ans(ans, s, c);
	ans[cnt_word] = 0;
	return (ans);
}
