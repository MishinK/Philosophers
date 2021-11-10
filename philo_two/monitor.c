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

#include "philo_two.h"

int						ft_check_die(t_data *data, t_philosopher *philo)
{
	if (philo->life_time > data->time_to_die)
	{
		sem_wait(g_entry_point);
		printf("%ldms \e[%um%i\e[0m DIE!!!!!!!!!!!!!! life_time = %ld\n",
		mtime() - data->start_time, 30 + philo->name, philo->name,
		philo->life_time);
		return (1);
	}
	sem_wait(philo->life_mutex);
	philo->life_time += 1;
	sem_post(philo->life_mutex);
	return (0);
}

int						ft_check_full_eat(t_data *data, t_table *table)
{
	if (data->must_to_eat > 0 && table->count_full == data->number_of_phil)
		return (1);
	return (0);
}

void					*potok_monitor(void *args)
{
	t_potok_monitor		*monitor;
	int					i;

	monitor = (t_potok_monitor *)args;
	while (1)
	{
		if (ft_check_full_eat(monitor->data, monitor->table))
			return (0);
		usleep_fix(1);
		i = 0;
		while (i < monitor->data->number_of_phil)
		{
			if (ft_check_die(monitor->data, monitor->philo[i]))
				return (0);
			i++;
		}
	}
	return (0);
}
