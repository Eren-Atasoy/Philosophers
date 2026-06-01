/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eratasoy <eratasoy@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 20:20:04 by eratasoy          #+#    #+#             */
/*   Updated: 2026/06/01 15:51:12 by eratasoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_is_dead(t_table *table)
{
	int	res;

	pthread_mutex_lock(&table->dead_mutex);
	res = table->dead_flag;
	pthread_mutex_unlock(&table->dead_mutex);
	if (res)
		return (1);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->table->philo_count == 1)
	{
		pthread_mutex_lock(philo->first_fork);
		log_action(philo, "has taken a fork");
		military_sleep(philo->table, philo->table->time_to_die);
		pthread_mutex_unlock(philo->first_fork);
		return (NULL);
	}
	if (philo->philo_id_number % 2 == 0)
		military_sleep(philo->table, 1);
	while (1)
	{
		if (philo_is_dead(philo->table))
			break ;
		take_forks(philo);
		philo_eat(philo);
		leave_forks(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
