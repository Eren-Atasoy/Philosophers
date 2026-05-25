/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eratasoy <eratasoy@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 20:18:52 by eratasoy          #+#    #+#             */
/*   Updated: 2026/05/25 20:39:33 by eratasoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_threads(t_table *table, int limit)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		pthread_join(table->philo_array[i].thread_id_number, NULL);
		i++;
	}
}

int	table_start_threads(t_table *table)
{
	int	i;

	table->start_time = time_ms_calc();
	i = 0;
	while (i < table->philo_count)
	{
		table->philo_array[i].last_meal_time = table->start_time;
		if (pthread_create(&table->philo_array[i].thread_id_number, NULL,
				philo_routine, &table->philo_array[i]) != 0)
		{
			pthread_mutex_lock(&table->dead_mutex);
			table->dead_flag = 1;
			pthread_mutex_unlock(&table->dead_mutex);
			join_threads(table, i);
			return (0);
		}
		i++;
	}
	observe_philosophers(table);
	join_threads(table, table->philo_count);
	return (1);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (!table_parse_args(&table, argc, argv))
		return (1);
	if (!table_init(&table))
	{
		write(2, "Error: Initialization failed.\n", 30);
		return (1);
	}
	if (!table_start_threads(&table))
	{
		write(2, "Error: Simulation failed.\n", 26);
		clean_table(&table);
		return (1);
	}
	clean_table(&table);
	return (0);
}
