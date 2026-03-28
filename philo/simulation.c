#include "philo.h"

int	start_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor_tid;

	data->start_time = get_time();
	i = 0;
	while (i < data->num_of_philos)
	{
		data->philos[i].last_meal_time = get_time();
		if (pthread_create(&data->philos[i].thread_id, NULL,
				routine, &data->philos[i]) != 0)
			return (0);
		i++;
	}
	if (pthread_create(&monitor_tid, NULL, monitor, data) != 0)
		return (0);
	i = 0;
	while (i < data->num_of_philos)
		pthread_join(data->philos[i++].thread_id, NULL);
	pthread_join(monitor_tid, NULL);
	return (1);
}
