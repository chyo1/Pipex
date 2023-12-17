/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:28:09 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/12/15 15:28:09 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

static unsigned int	get_word_cnt(const char *str, char c)
{
	unsigned int	cnt_word;
	unsigned int	idx;
	unsigned int	cnt;
	char			check_char;

	cnt_word = 0;
	idx = 0;
	while (str[idx])
	{
		if (str[idx] != c && str[idx] != '"' && str[idx] != 39)
		{
			cnt_word++;
			while (str[idx] && str[idx] != c)
				idx++;
			// printf("check_space\n");
		}
		else if (str[idx] == '"' || str[idx] == 39)
		{
			// printf("check_quotes\n");
			cnt_word++;
			cnt = 0;
			if (str[idx] && (str[idx] == 39 || str[idx] == '"'))
			{
				check_char = str[idx];
				idx++;
			}
			// printf("cnt : %d\n", cnt);
			while (str[idx] && str[idx] != check_char)
			{
				if (str[idx] == '\\')
					idx++;
				idx++;
			}
			idx++;
			// printf("cnt : %d, str[idx] : %d\n", cnt, str[idx]);
		}
		else
			idx++;
	}
	// printf("cnt_word : %d\n", cnt_word);
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

static void put_ans_idx(char **ans, const char *str, unsigned int len, unsigned int *ans_idx)
{
	ans[*ans_idx] = (char *)malloc(sizeof(char) * (len));
	if (ans[*ans_idx] == NULL)
		print_error_n_exit(MALLOC_ERROR);
	get_wrd(str, ans[*ans_idx], 0, len - 1);
	(*ans_idx)++;
}

static void	fill_ans(char **ans, const char *str, char c)
{
	unsigned int	s;
	unsigned int	idx;
	unsigned int	ans_idx;
	unsigned int	cnt;
	char			check_char;

	idx = 0;
	ans_idx = 0;
	while (str[idx])
	{
		if (str[idx] != c && str[idx] != '"' && str[idx] != 39)
		{
			s = idx;
			while (str[idx] && str[idx] != c)
				idx++;
			put_ans_idx(ans, &str[s], idx - s + 1, &ans_idx);
		}
		else if (str[idx] == '"' || str[idx] == 39)
		{
			cnt = 0;
			if (str[idx] && (str[idx] == 39 || str[idx] == '"'))
			{
				check_char = str[idx];
				idx++;
			}
			s = idx;
			while (str[idx] && str[idx] != check_char)
			{
				if (str[idx] == '\\')
					idx++;
				idx++;
			}
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

	cnt_word = get_word_cnt(s, c);
	ans = (char **)malloc(sizeof(char *) * (cnt_word + 1));
	if (ans == NULL)
		print_error_n_exit(MALLOC_ERROR);
	fill_ans(ans, s, c);
	ans[cnt_word] = 0;
	return (ans);
}


char	*ft_strchr(const char *s, int c)
{
	char	cmp;

	cmp = (char)c;
	while (*s)
	{
		if (cmp == *s)
			return ((char *)s);
			s++;
	}
	if (cmp == 0)
		return ((char *)s);
	return (NULL);
}