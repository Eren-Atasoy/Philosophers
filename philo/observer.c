/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eratasoy <eratasoy@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 20:19:08 by eratasoy          #+#    #+#             */
/*   Updated: 2026/05/25 20:19:09 by eratasoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	state_control(t_table *table, t_philosopher *philo)
{
	size_t	current_time;

	current_time = time_ms_calc();
	pthread_mutex_lock(&philo->mutex_meal);
	if ((current_time - philo->last_meal_time) > table->time_to_die)
	{
		pthread_mutex_lock(&table->dead_mutex);
		table->dead_flag = 1;
		pthread_mutex_unlock(&table->dead_mutex);
		pthread_mutex_lock(&table->log_mutex);
		printf("%zu %d died\n", current_time - table->start_time,
			philo->philo_id_number);
		pthread_mutex_unlock(&table->log_mutex);
		pthread_mutex_unlock(&philo->mutex_meal);
		return (1);
	}
	if (table->nb_times_to_eat != -1
		&& philo->eat_count >= table->nb_times_to_eat)
	{
		pthread_mutex_unlock(&philo->mutex_meal);
		return (2);
	}
	pthread_mutex_unlock(&philo->mutex_meal);
	return (0);
}

static int	check_all_full(t_table *table, int finished_eating)
{
	if (finished_eating == table->philo_count)
	{
		pthread_mutex_lock(&table->dead_mutex);
		table->dead_flag = 1;
		pthread_mutex_unlock(&table->dead_mutex);
		return (1);
	}
	return (0);
}

void	observe_philosophers(t_table *table)
{
	int	i;
	int	finished_eating;
	int	state;

	i = 0;
	finished_eating = 0;
	while (1)
	{
		if (i == table->philo_count)
		{
			i = 0;
			finished_eating = 0;
			usleep(1000);
		}
		state = state_control(table, &table->philo_array[i]);
		if (state == 1)
			return ;
		if (state == 2)
			finished_eating++;
		if (check_all_full(table, finished_eating))
			return ;
		i++;
	}
}
