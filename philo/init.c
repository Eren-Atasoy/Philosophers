#include "philo.h"

static int	initialize_mutex(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (0);
	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

static int	initialize_philos(t_data *data)
{
	int	i;
	int	n;

	i = 0;
	n = data->num_of_philos;
	while (i < n)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].data = data;
		if (pthread_mutex_init(&data->philos[i].meal_lock, NULL) != 0)
			return (0);
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % n];
		i++;
	}
	return (1);
}

int	init_data(t_data *data)
{
	data->dead = 0;
	data->all_ate = 0;
	data->philos = malloc(sizeof(t_philo) * data->num_of_philos);
	if (!data->philos)
		return (0);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!data->forks)
	{
		free(data->philos);
		return (0);
	}
	if (!initialize_mutex(data))
		return (0);
	if (!initialize_philos(data))
		return (0);
	return (1);
}
