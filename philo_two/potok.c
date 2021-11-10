/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   potok.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashea <ashea@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 11:01:59 by ashea             #+#    #+#             */
/*   Updated: 2021/03/30 11:02:00 by ashea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void		ft_thinking(t_data *data, t_philosopher *philosopher)
{
	sem_wait(g_entry_point);
	printf("%ldms \e[%um%i\e[0m is thinking\n",
	mtime() - data->start_time, 30 + philosopher->name,
	philosopher->name);
	sem_post(g_entry_point);
}

void		ft_taken_fork(t_data *data,
t_philosopher *philosopher, t_table *table)
{
	sem_wait(table->forks);
	sem_wait(g_entry_point);
	printf("%ldms \e[%um%i\e[0m has taken a fork (1/2)\n",
	mtime() - data->start_time, 30 + philosopher->name,
	philosopher->name);
	sem_post(g_entry_point);
	sem_wait(table->forks);
	sem_wait(g_entry_point);
	printf("%ldms \e[%um%i\e[0m has taken a fork (2/2)\n",
	mtime() - data->start_time, 30 + philosopher->name,
	philosopher->name);
	sem_post(g_entry_point);
}

void		ft_eating(t_data *data,
t_philosopher *philosopher, t_table *table)
{
	sem_wait(philosopher->life_mutex);
	philosopher->life_time = 0;
	sem_post(philosopher->life_mutex);
	sem_wait(g_entry_point);
	printf("%ldms \e[%um%i\e[0m is eating\n",
	mtime() - data->start_time, 30 + philosopher->name,
	philosopher->name);
	sem_post(g_entry_point);
	usleep_fix(data->time_to_eat);
	sem_post(table->forks);
	sem_post(table->forks);
	if (philosopher->count_to_eat > 0)
		philosopher->count_to_eat--;
	if (philosopher->count_to_eat == 0)
		table->count_full++;
}

void		ft_sleeping(t_data *data, t_philosopher *philosopher)
{
	sem_wait(g_entry_point);
	printf("%ldms \e[%um%i\e[0m is sleeping\n",
	mtime() - data->start_time, 30 + philosopher->name,
	philosopher->name);
	sem_post(g_entry_point);
	usleep_fix(data->time_to_sleep);
}

void		*potok(void *args)
{
	t_potok_param	*param;
	int				a;

	param = (t_potok_param *)args;
	a = param->philo->name;
	while (1)
	{
		if (a % 2 == 1)
		{
			ft_thinking(param->data, param->philo);
			ft_taken_fork(param->data, param->philo, param->table);
			ft_eating(param->data, param->philo, param->table);
			if (param->philo->count_to_eat == 0)
				return (0);
			ft_sleeping(param->data, param->philo);
		}
		else
		{
			a++;
			usleep_fix(5);
		}
	}
	return (0);
}
