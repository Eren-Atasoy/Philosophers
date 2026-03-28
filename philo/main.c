#include "philo.h"

int	ft_advanced_atoi(const char *str)
{
	long	sum;
	int		i;

	sum = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		return (-1);
	if (str[i] == '\0')
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			sum = sum * 10 + (str[i] - '0');
		else
			return (-1);
		if (sum > 2147483647)
			return (-1);
		i++;
	}
	return ((int)sum);
}

static int	validate_parsed_data(t_data *data, int argc)
{
	if (data->num_of_philos < 0 || (int)data->time_to_die < 0
		|| (int)data->time_to_eat < 0 || (int)data->time_to_sleep < 0
		|| (argc == 6 && data->num_times_to_eat < 0))
	{
		write(2, "Hata: Argumanlar sadece pozitif sayi olmalidir.\n", 48);
		return (0);
	}
	if (data->num_of_philos == 0)
	{
		write(2, "Hata: En az 1 filozof olmalidir.\n", 34);
		return (0);
	}
	if (argc == 6 && data->num_times_to_eat == 0)
		return (-2);
	return (1);
}

int	check_args(int argc, char **argv, t_data *data)
{
	if (argc != 5 && argc != 6)
	{
		write(2, "Hata: Hatali arguman sayisi.\n", 29);
		return (0);
	}
	data->num_of_philos = ft_advanced_atoi(argv[1]);
	data->time_to_die = ft_advanced_atoi(argv[2]);
	data->time_to_eat = ft_advanced_atoi(argv[3]);
	data->time_to_sleep = ft_advanced_atoi(argv[4]);
	if (argc == 6)
		data->num_times_to_eat = ft_advanced_atoi(argv[5]);
	else
		data->num_times_to_eat = -1;
	return (validate_parsed_data(data, argc));
}

void	clean_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->print_lock);
	free(data->forks);
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		status;

	status = check_args(argc, argv, &data);
	if (status == 0)
		return (1);
	else if (status == -2)
		return (0);
	if (!init_data(&data))
	{
		write(2, "Hata: Baslatma sirasinda hata.\n", 31);
		return (1);
	}
	if (!start_simulation(&data))
	{
		write(2, "Hata: Thread baslatilirken sorun olustu.\n", 41);
		clean_data(&data);
		return (1);
	}
	clean_data(&data);
	return (0);
}
