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

#include "philo_three.h"

void			ft_start_simulation(t_param *param)
{
	pid_t		*pid;
	pthread_t	tid;
	int			i;

	if (!(pid = (pid_t *)malloc(sizeof(pid_t)
	* param->monitor->data->number_of_phil)))
		printf("error malloc\n");
	i = 0;
	while (i < param->monitor->data->number_of_phil)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			param->monitor->philo = param->param[i]->philo;
			if (pthread_create(&tid, NULL, potok_monitor, param->monitor))
				printf("error thread\n");
			potok(param->param[i]);
			pthread_join(tid, NULL);
			sem_post(g_entry_point2);
			exit(0);
		}
		i++;
	}
	sem_wait(g_entry_point2);
	ft_free_all(param, pid);
}

int				main(int argc, char **argv)
{
	t_data		data;
	t_param		*param;

	ft_init_data(&data, argc, argv);
	param = ft_init_all(&data);
	sem_unlink("/g_entry_point");
	sem_unlink("/g_entry_point2");
	g_entry_point = sem_open("/g_entry_point", O_CREAT, 0777, 1);
	if (g_entry_point == (sem_t *)SEM_FAILED || g_entry_point == NULL)
		printf("error g_entry_point\n");
	g_entry_point2 = sem_open("/g_entry_point2", O_CREAT, 0777, 0);
	if (g_entry_point2 == (sem_t *)SEM_FAILED || g_entry_point2 == NULL)
		printf("error g_entry_point\n");
	ft_start_simulation(param);
	return (0);
}
