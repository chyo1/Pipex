/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:47:26 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/10/14 12:42:01 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	change_i_to_c(char *str, long long n)
{
	int				minus;
	unsigned int	idx;

	minus = 0;
	idx = 0;
	if (n < 0)
	{
		minus = 1;
		n = -n;
	}
	else if (n == 0)
		str[idx++] = '0';
	while (n != 0)
	{
		str[idx++] = (n % 10) + '0';
		n /= 10;
	}
	if (minus)
		str[idx++] = '-';
}

static unsigned int	get_len(int n)
{
	unsigned int	idx;

	idx = 0;
	if (n <= 0)
		idx = 1;
	while (n != 0)
	{
		idx++;
		n /= 10;
	}
	return (idx);
}

static void	str_swap(char *ans, unsigned int len)
{
	unsigned int	idx;
	char			tmp;

	ans[len] = '\0';
	idx = 0;
	while (idx < len / 2)
	{
		tmp = ans[idx];
		ans[idx] = ans[len - idx - 1];
		ans[len - idx -1] = tmp;
		idx++;
	}
}

static char	*ft_itoa(int n)
{
	char			*ans;
	unsigned int	len;

	len = get_len(n);
	ans = (char *)malloc(sizeof(char) * (len + 1));
	if (ans == NULL)
		print_error_n_exit(MALLOC_ERROR);
	change_i_to_c(ans, (long long)n);
	str_swap(ans, len);
	return (ans);
}

char	*make_file_name(char *name)
{
	int		i;
	char	*file_name;
	char	*num;

	i = 1;
	while (1)
	{
		num = ft_itoa(i);
		file_name = malloc(ft_strlen(name) + ft_strlen(num) + 1);
		if (file_name == NULL)
			print_error_n_exit(MALLOC_ERROR);
		ft_strlcpy(file_name, name, ft_strlen(name) + 1);
		ft_strlcat(file_name, num, ft_strlen(name) + ft_strlen(num) + 1);
		free(num);
		if (access((const char *)file_name, F_OK) != 0)
			return (file_name);
		i++;
		free(file_name);
	}
	return (file_name);
}
