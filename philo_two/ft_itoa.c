/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 16:17:06 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/22 21:53:49 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static	void	*ft_bzero(void *buf, size_t n)
{
	return (memset(buf, 0, n));
}

static	void	*ft_calloc(size_t num, size_t size)
{
	unsigned char *new;

	if (!(new = malloc(size * num)))
		return (NULL);
	ft_bzero(new, num * size);
	return ((void *)new);
}

static	char	itoc(int n)
{
	if (n / 10 != 0)
		return ('0');
	n = (n < 0) ? -n : n;
	return ('0' + n);
}

static	size_t	count(int n)
{
	size_t i;

	i = 0;
	if (n <= 0)
		i++;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	char	*str;
	size_t	size;

	size = count(n);
	if (!(str = (char *)ft_calloc(size + 1, sizeof(char))))
		return (NULL);
	str[size--] = '\0';
	if (n < 0)
		str[0] = '-';
	if (n == 0)
		str[0] = '0';
	while (n)
	{
		str[size--] = itoc(n % 10);
		n /= 10;
	}
	return (str);
}
