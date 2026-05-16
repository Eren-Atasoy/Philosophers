#include "philo.h"

void	clean_table(t_table *table)
{
	int	i;

	if (table->fork_array)
	{
		i = 0;
		while (i++ < table->philo_count)
			pthread_mutex_destroy(&table->fork_array[i]);
		free(table->fork_array);
	}
	if (table->philo_array)
	{
		i = 0;
		while (i++ < table->philo_count)
			pthread_mutex_destroy(&table->philo_array[i].mutex_meal);
		free(table->philo_array);
	}
	pthread_mutex_destroy(&table->dead_mutex);
	pthread_mutex_destroy(&table->log_mutex);
}
