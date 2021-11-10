/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashea <ashea@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 10:57:03 by ashea             #+#    #+#             */
/*   Updated: 2021/03/30 10:57:05 by ashea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

long	mtime(void)
{
	struct timeval	t;
	long			mt;

	gettimeofday(&t, NULL);
	mt = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (mt);
}

void	usleep_fix(long time)
{
	long	t;

	t = mtime();
	while (mtime() - t < time)
		usleep(1);
}

int		max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int		min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	ft_error_argc(void)
{
	printf("error: only positive int arguments expected\n");
	exit(-1);
}
