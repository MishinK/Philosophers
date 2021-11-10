/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashea <ashea@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 10:58:16 by ashea             #+#    #+#             */
/*   Updated: 2021/03/30 10:58:17 by ashea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void				ft_init_data(t_data *data, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("wrong number argument\n");
		exit(-1);
	}
	if (argv[1][0] > '9' || argv[1][0] < '0' ||
	(data->number_of_phil = ft_atoi(argv[1])) <= 0)
		ft_error_argc();
	if (argv[2][0] > '9' || argv[2][0] < '0' ||
	(data->time_to_die = ft_atoi(argv[2])) <= 0)
		ft_error_argc();
	if (argv[3][0] > '9' || argv[3][0] < '0' ||
	(data->time_to_eat = ft_atoi(argv[3])) <= 0)
		ft_error_argc();
	if (argv[4][0] > '9' || argv[4][0] < '0' ||
	(data->time_to_sleep = ft_atoi(argv[4])) <= 0)
		ft_error_argc();
	if (argc == 6)
		if (argv[5][0] > '9' || argv[5][0] < '0' ||
		(data->must_to_eat = ft_atoi(argv[5])) <= 0)
			ft_error_argc();
	if (argc == 5)
		data->must_to_eat = -1;
	data->start_time = mtime();
}

t_table				*ft_init_table(t_data *data)
{
	t_table			*table;
	int				i;

	if (!(table = (t_table *)malloc(sizeof(t_table) * 1)))
		printf("error malloc\n");
	if (!(table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
	* data->number_of_phil)))
		printf("error malloc\n");
	i = 0;
	while (i < data->number_of_phil)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	table->count_full = 0;
	return (table);
}

t_philosopher		**ft_init_all_philosopher(t_data *data)
{
	t_philosopher	**philo;
	int				i;

	if (!(philo = (t_philosopher **)malloc(sizeof(t_philosopher *)
	* data->number_of_phil)))
		printf("error malloc\n");
	i = 0;
	while (i < data->number_of_phil)
	{
		if (!(philo[i] = (t_philosopher *)malloc(sizeof(t_philosopher) * 1)))
			printf("error malloc\n");
		philo[i]->name = i + 1;
		philo[i]->left_fork = i;
		philo[i]->right_fork = (i + 1) % data->number_of_phil;
		philo[i]->count_to_eat = data->must_to_eat;
		philo[i]->life_time = 0;
		pthread_mutex_init(&philo[i]->life_mutex, NULL);
		i++;
	}
	return (philo);
}

t_potok_param		**ft_init_param(t_philosopher **philo,
t_table *table, t_data *data)
{
	t_potok_param	**param;
	int				i;

	if (!(param = (t_potok_param **)malloc(sizeof(t_potok_param *)
	* data->number_of_phil)))
		printf("error malloc\n");
	i = 0;
	while (i < data->number_of_phil)
	{
		if (!(param[i] = (t_potok_param *)malloc(sizeof(t_potok_param) * 1)))
			printf("error malloc\n");
		param[i]->philo = philo[i];
		param[i]->data = data;
		param[i]->table = table;
		i++;
	}
	return (param);
}

t_param				*ft_init_all(t_data *data)
{
	t_param			*param;
	t_table			*table;
	t_philosopher	**philo;

	if (!(param = (t_param *)malloc(sizeof(t_param) * 1)))
		printf("error malloc\n");
	if (!(param->monitor = (t_potok_monitor *)malloc(sizeof(t_potok_monitor))))
		printf("error malloc\n");
	table = ft_init_table(data);
	philo = ft_init_all_philosopher(data);
	param->monitor->data = data;
	param->monitor->table = table;
	param->monitor->philo = philo;
	param->param = ft_init_param(philo, table, data);
	return (param);
}
