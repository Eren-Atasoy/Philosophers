/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eratasoy <eratasoy@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 20:20:08 by eratasoy          #+#    #+#             */
/*   Updated: 2026/05/25 20:20:10 by eratasoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	time_ms_calc(void)
{
	struct timeval	tv;
	size_t			ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}

void	military_sleep(t_table *table, size_t sleep_time)
{
	size_t	start_sleep_time;
	size_t	last_time;

	start_sleep_time = time_ms_calc();
	last_time = 0;
	while (last_time < sleep_time)
	{
		usleep(500);
		pthread_mutex_lock(&table->dead_mutex);
		if (table->dead_flag)
		{
			pthread_mutex_unlock(&table->dead_mutex);
			return ;
		}
		pthread_mutex_unlock(&table->dead_mutex);
		last_time = time_ms_calc() - start_sleep_time;
	}
}

void	log_action(t_philosopher *philo, char *log_message)
{
	size_t	elapsed_time;

	pthread_mutex_lock(&philo->table->log_mutex);
	elapsed_time = time_ms_calc() - philo->table->start_time;
	if (philo_is_dead(philo->table))
	{
		pthread_mutex_unlock(&philo->table->log_mutex);
		return ;
	}
	printf("%zu %d %s\n", elapsed_time, philo->philo_id_number, log_message);
	pthread_mutex_unlock(&philo->table->log_mutex);
}

void	clean_table(t_table *table)
{
	int	i;

	i = 0;
	while (table->fork_array && i < table->forks_init_count)
	{
		pthread_mutex_destroy(&table->fork_array[i]);
		i++;
	}
	free(table->fork_array);
	i = 0;
	while (table->philo_array && i < table->philos_init_count)
	{
		pthread_mutex_destroy(&table->philo_array[i].mutex_meal);
		i++;
	}
	free(table->philo_array);
	if (table->dead_mutex_flag == 1)
		pthread_mutex_destroy(&table->dead_mutex);
	if (table->log_mutex_flag == 1)
		pthread_mutex_destroy(&table->log_mutex);
}
