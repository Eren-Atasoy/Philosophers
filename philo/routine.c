#include "philo.h"

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, "has taken a fork");
	if (philo->data->num_of_philos == 1)
	{
		ft_usleep(philo->data->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	print_message(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	philo_think(t_philo *philo)
{
	size_t	tt_think;

	print_message(philo, "is thinking");
	if (philo->data->num_of_philos % 2 == 1)
	{
		tt_think = (philo->data->time_to_eat * 2) - philo->data->time_to_sleep;
		if ((long)tt_think > 0)
			ft_usleep(tt_think * 0.4);
	}
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->id % 2 == 0)
		ft_usleep(p->data->time_to_eat / 2);
	else if (p->data->num_of_philos % 2 != 0 && p->id == p->data->num_of_philos)
		ft_usleep(p->data->time_to_eat);
	while (!check_death(p->data))
	{
		philo_eat(p);
		if (p->data->num_times_to_eat != -1
			&& p->meals_eaten >= p->data->num_times_to_eat)
			break ;
		print_message(p, "is sleeping");
		ft_usleep(p->data->time_to_sleep);
		philo_think(p);
	}
	return (NULL);
}

static int	check_philos_status(t_data *d, int i, int *all_ate)
{
	pthread_mutex_lock(&d->philos[i].meal_lock);
	if (get_time() - d->philos[i].last_meal_time >= d->time_to_die)
	{
		pthread_mutex_unlock(&d->philos[i].meal_lock);
		pthread_mutex_lock(&d->print_lock);
		pthread_mutex_lock(&d->dead_lock);
		if (!d->dead)
		{
			d->dead = 1;
			printf("%zu %d died\n", get_time() - d->start_time,
				d->philos[i].id);
		}
		pthread_mutex_unlock(&d->dead_lock);
		pthread_mutex_unlock(&d->print_lock);
		return (1);
	}
	if (d->num_times_to_eat != -1
		&& d->philos[i].meals_eaten < d->num_times_to_eat)
		*all_ate = 0;
	pthread_mutex_unlock(&d->philos[i].meal_lock);
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*d;
	int		i;
	int		all_ate;

	d = (t_data *)arg;
	while (!check_death(d))
	{
		i = -1;
		all_ate = 1;
		while (++i < d->num_of_philos)
		{
			if (check_philos_status(d, i, &all_ate))
				return (NULL);
		}
		if (d->num_times_to_eat != -1 && all_ate)
			break ;
		usleep(1000);
	}
	return (NULL);
}
