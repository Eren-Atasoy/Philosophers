#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_table	t_table;


typedef struct s_philosopher
{
	int				philo_id_number;
	int				eat_count;
	pthread_t		thread_id_number;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	pthread_mutex_t	mutex_meal;
	size_t			last_meal_time;
	t_table			*table;
}	t_philo;


typedef struct s_table
{
	int				philo_count;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				nb_times_to_eat;
	int				dead_flag;
	size_t			start_time;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	*fork_array;
	t_philo			*philo_array;
}	t_table;


#endif