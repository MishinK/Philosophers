/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashea <ashea@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 12:06:35 by ashea             #+#    #+#             */
/*   Updated: 2021/03/30 12:06:38 by ashea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_start_simulation(t_param *param)
{
	pthread_t	*tid;
	int			i;

	pthread_mutex_init(&g_entry_point, NULL);
	if (!(tid = (pthread_t *)malloc(sizeof(pthread_t) *
	(param->monitor->data->number_of_phil + 1))))
		printf("error malloc\n");
	if (pthread_create(&tid[param->monitor->data->number_of_phil],
	NULL, potok_monitor, param->monitor))
		printf("error thread\n");
	i = 0;
	while (i < param->monitor->data->number_of_phil)
	{
		if (pthread_create(&tid[i], NULL, potok, param->param[i]))
			printf("error thread\n");
		i++;
	}
	if (pthread_join(tid[param->monitor->data->number_of_phil], NULL))
		printf("error thread\n");
	free(tid);
	ft_free_all(param);
}

int		main(int argc, char **argv)
{
	t_data		data;
	t_param		*param;

	ft_init_data(&data, argc, argv);
	param = ft_init_all(&data);
	ft_start_simulation(param);
	return (0);
}
