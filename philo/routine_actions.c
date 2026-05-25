/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eratasoy <eratasoy@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 20:19:59 by eratasoy          #+#    #+#             */
/*   Updated: 2026/05/25 20:39:33 by eratasoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philosopher *philo)
{
	pthread_mutex_lock(philo->first_fork);
	log_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->second_fork);
	log_action(philo, "has taken a fork");
}

void	philo_eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->mutex_meal);
	philo->last_meal_time = time_ms_calc();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->mutex_meal);
	log_action(philo, "is eating");
	military_sleep(philo->table, philo->table->time_to_eat);
}

void	leave_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

void	philo_sleep(t_philosopher *philo)
{
	log_action(philo, "is sleeping");
	military_sleep(philo->table, philo->table->time_to_sleep);
}

void	philo_think(t_philosopher *philo)
{
	log_action(philo, "is thinking");
}
