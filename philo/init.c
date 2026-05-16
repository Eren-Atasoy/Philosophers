#include "philo.h"

static int	table_mutex_initialization(t_table *table)
{
	int	i;

	if (pthread_mutex_init(&table->log_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&table->dead_mutex, NULL) != 0)
		return (0);

	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_mutex_init(&table->fork_array[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

static void philo_forks_assignment(t_philo *current_philo, t_table *table, int i)
{
	int	left_fork;
	int	right_fork;

	left_fork= i;
	right_fork = (i + 1) % table->philo_count;
	if (left_fork < right_fork)
	{
		current_philo->first_fork = &table->fork_array[left_fork];
		current_philo->second_fork = &table->fork_array[right_fork];
	}
	else
	{
		current_philo->first_fork = &table->fork_array[right_fork];
		current_philo->second_fork = &table->fork_array[left_fork];
	}
}

static int	philo_initialization(t_table *table)
{
	int		i;
	t_philo	*current_philo;

	i = 0;
	while (i < table->philo_count)
	{
		current_philo = &table->philo_array[i];
		current_philo->philo_id_number = i + 1;
		current_philo->eat_count = 0;
		current_philo->last_meal_time = 0;
		current_philo->table = table;
		if (pthread_mutex_init(&current_philo->mutex_meal, NULL) != 0)
			return (0);
		philo_forks_assignment(current_philo, table, i);
		i++;
	}
	return (1);
}

int	table_init(t_table *table)
{
	table->philo_array = NULL;
	table->fork_array = NULL;
	table->philo_array = malloc(sizeof(t_philo) * table->philo_count);
	if (!table->philo_array)
		return (0);
	table->fork_array = malloc(sizeof(pthread_mutex_t) * table->philo_count);
	if (!table->fork_array)
	{
		clean_table(table);
		return (0);
	}
	table->dead_flag = 0;
	if (!philo_initialization(table))
	{
		clean_table(table);
		return (0);
	}
	if (!table_mutex_initialization(table))
	{
		clean_table(table);
		return (0);
	}
	return (1);
}
