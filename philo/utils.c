#include "philo.h"

size_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(size_t milliseconds)
{
	size_t	start;
	start = get_time();
	while ((get_time() - start) < milliseconds)
	{
		usleep(500);
	}
}

int	check_death(t_data *data)
{
	int	is_dead;

	pthread_mutex_lock(&data->dead_lock);
	is_dead = data->dead;
	pthread_mutex_unlock(&data->dead_lock);
	return (is_dead);
}

void	print_message(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->print_lock);
	if (!check_death(philo->data))
	{
		printf("%zu %d %s\n", get_time() - philo->data->start_time,
			philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->print_lock);
}
