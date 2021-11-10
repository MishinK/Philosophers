/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrock <bbrock@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 14:33:18 by bbrock            #+#    #+#             */
/*   Updated: 2021/01/22 21:53:03 by bbrock           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static	int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static	int	ctoi(const char c)
{
	return (ft_isdigit(c)) ? (c - '0') : 0;
}

int			ft_atoi(const char *str)
{
	int			sign;
	long long	res;

	res = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'
			|| *str == '\v' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
		sign = (*str++ == '-') ? -1 : 1;
	while (ft_isdigit(*str))
	{
		res = (res == 0) ? sign * ctoi(*str) : res * 10 + sign * ctoi(*str);
		if (res % 10 != sign * ctoi(*str) % 10)
			return ((sign < 0) ? 0 : -1);
		str++;
	}
	return (res);
}
