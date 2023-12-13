/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:40:29 by hyowchoi          #+#    #+#             */
/*   Updated: 2023/10/13 15:59:44 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(char *s1)
{
	char	*a;
	size_t	len;

	len = ft_strlen(s1);
	a = (char *)malloc(sizeof(char) * (len + 1));
	if (a == NULL)
		return (NULL);
	ft_strlcpy(a, s1, len + 1);
	return (a);
}

size_t	ft_strlcpy(char *dst, char *src, size_t detsize)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (detsize != 0)
	{
		while (i + 1 < detsize && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_len);
}

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	i;
	size_t	len_d;
	size_t	len_s;

	if (!dst && !size)
		return (ft_strlen(src));
	len_d = ft_strlen(dst);
	len_s = ft_strlen(src);
	if (size < len_d)
		return (len_s + size);
	if (size > 0)
	{
		i = 0;
		while (len_d + i + 1 < size && src[i] != '\0')
		{
			dst[len_d + i] = src[i];
			i++;
		}
		dst[len_d + i] = '\0';
	}
	return (len_d + len_s);
}

size_t	ft_strlen(const char *s)
{
	size_t	n;

	n = 0;
	while (*s)
	{
		n++;
		s++;
	}
	return (n);
}
