/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashea <ashea@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 10:48:23 by ashea             #+#    #+#             */
/*   Updated: 2021/03/30 10:48:27 by ashea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct		s_data
{
	int				number_of_phil;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			must_to_eat;
	long			start_time;
}					t_data;

typedef struct		s_table
{
	sem_t			*forks;
	int				count_full;
}					t_table;

typedef struct		s_philosopher
{
	int				name;
	int				left_fork;
	int				right_fork;
	long			count_to_eat;
	long			life_time;
	sem_t			*life_mutex;
}					t_philosopher;

typedef struct		s_potok_param
{
	t_data			*data;
	t_table			*table;
	t_philosopher	*philo;
}					t_potok_param;

typedef struct		s_potok_monitor
{
	t_data			*data;
	t_table			*table;
	t_philosopher	**philo;
}					t_potok_monitor;

typedef struct		s_param
{
	t_potok_param	**param;
	t_potok_monitor	*monitor;
}					t_param;

sem_t				*g_entry_point;
int					ft_atoi(const char *str);
char				*ft_itoa(int n);
long				mtime(void);
void				usleep_fix(long time);
int					max(int a, int b);
int					min(int a, int b);
void				ft_error_argc(void);
void				ft_init_data(t_data *data, int argc, char **argv);
t_table				*ft_init_table(t_data *data);
t_philosopher		**ft_init_all_philosopher(t_data *data);
t_potok_param		**ft_init_param(t_philosopher **philo,
					t_table *table, t_data *data);
t_param				*ft_init_all(t_data *data);
void				ft_free_table(t_table *table);
void				ft_free_all_philosopher(t_philosopher **philo, int size);
void				ft_free_param(t_potok_param **param, int size);
void				ft_free_all(t_param *param);
void				ft_thinking(t_data *data, t_philosopher *philosopher);
void				ft_taken_fork(t_data *data,
					t_philosopher *philosopher, t_table *table);
void				ft_eating(t_data *data,
					t_philosopher *philosopher, t_table *table);
void				ft_sleeping(t_data *data, t_philosopher *philosopher);
void				*potok(void *args);
int					ft_check_die(t_data *data, t_philosopher *philo);
int					t_check_full_eat(t_data *data, t_table *table);
void				*potok_monitor(void *args);
void				ft_start_simulation(t_param *param);

#endif
