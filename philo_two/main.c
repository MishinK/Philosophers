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

#include "philo_two.h"

void			ft_start_simulation(t_param *param)
{
	pthread_t	*tid;
	int			i;

	sem_unlink("g_entry_point");
	g_entry_point = sem_open("g_entry_point", O_CREAT, 0777, 1);
	if (g_entry_point == (sem_t *)SEM_FAILED || g_entry_point == NULL)
		printf("error g_entry_point\n");
	if (!(tid = (pthread_t *)malloc(sizeof(pthread_t)
	* (param->monitor->data->number_of_phil + 1))))
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

int				main(int argc, char **argv)
{
	t_data		data;
	t_param		*param;

	ft_init_data(&data, argc, argv);
	param = ft_init_all(&data);
	ft_start_simulation(param);
	return (0);
}
