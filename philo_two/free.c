/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashea <ashea@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 10:59:09 by ashea             #+#    #+#             */
/*   Updated: 2021/03/30 10:59:11 by ashea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	ft_free_table(t_table *table)
{
	free(table);
}

void	ft_free_all_philosopher(t_philosopher **philo, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(philo[i]);
		i++;
	}
	free(philo);
}

void	ft_free_param(t_potok_param **param, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(param[i]);
		i++;
	}
	free(param);
}

void	ft_free_all(t_param *param)
{
	ft_free_table(param->monitor->table);
	ft_free_all_philosopher(param->monitor->philo,
	param->monitor->data->number_of_phil);
	ft_free_param(param->param, param->monitor->data->number_of_phil);
	free(param->monitor);
	free(param);
}
