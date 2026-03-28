#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	size_t			last_meal_time;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_lock;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				num_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_times_to_eat;
	int				dead;
	int				all_ate;
	size_t			start_time;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_data;

int		init_data(t_data *data);
size_t	get_time(void);
void	ft_usleep(size_t milliseconds, t_data *data);
int		check_death(t_data *data);
void	print_message(t_philo *philo, char *msg);
void	*routine(void *arg);
void	*monitor(void *arg);
int		start_simulation(t_data *data);
void	clean_data(t_data *data);

#endif
