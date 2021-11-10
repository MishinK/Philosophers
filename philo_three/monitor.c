/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashea <ashea@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 11:03:07 by ashea             #+#    #+#             */
/*   Updated: 2021/03/30 11:03:08 by ashea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int						ft_check_die(t_data *data, t_philosopher *philo)
{
	if (philo->life_time > data->time_to_die)
	{
		sem_wait(g_entry_point);
		printf("%ldms \e[%um%i\e[0m DIE!!!!!!!!!!!!!! life_time = %ld\n",
		mtime() - data->start_time, 30 + philo->name, philo->name,
		philo->life_time);
		sem_post(g_entry_point2);
		return (1);
	}
	sem_wait(philo->life_mutex);
	philo->life_time += 1;
	sem_post(philo->life_mutex);
	return (0);
}

int						ft_check_full_eat(t_data *data, t_philosopher *philo)
{
	if (data->must_to_eat > 0 && philo->count_to_eat == 0)
		return (1);
	return (0);
}

void					*potok_monitor(void *args)
{
	t_potok_monitor		*monitor;

	monitor = (t_potok_monitor *)args;
	while (1)
	{
		if (ft_check_full_eat(monitor->data, monitor->philo))
			return (0);
		if (ft_check_die(monitor->data, monitor->philo))
			return (0);
		usleep_fix(1);
	}
	return (0);
}
