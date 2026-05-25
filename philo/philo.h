/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eratasoy <eratasoy@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 20:38:30 by eratasoy          #+#    #+#             */
/*   Updated: 2026/05/25 20:38:32 by eratasoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_table	t_table;

typedef struct s_philosopher
{
	int					philo_id_number;
	int					eat_count;
	pthread_t			thread_id_number;
	pthread_mutex_t		*first_fork;
	pthread_mutex_t		*second_fork;
	pthread_mutex_t		mutex_meal;
	size_t				last_meal_time;
	t_table				*table;
}						t_philosopher;

typedef struct s_table
{
	int					philo_count;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					nb_times_to_eat;
	int					dead_flag;
	size_t				start_time;
	pthread_mutex_t		dead_mutex;
	pthread_mutex_t		log_mutex;
	pthread_mutex_t		*fork_array;
	t_philosopher		*philo_array;
	int					forks_init_count;
	int					philos_init_count;
	int					log_mutex_flag;
	int					dead_mutex_flag;
}						t_table;

void					observe_philosophers(t_table *table);
int						philo_is_dead(t_table *table);
void					take_forks(t_philosopher *philo);
void					philo_eat(t_philosopher *philo);
void					leave_forks(t_philosopher *philo);
void					philo_sleep(t_philosopher *philo);
void					philo_think(t_philosopher *philo);

void					log_action(t_philosopher *philo, char *log_message);
void					military_sleep(t_table *table, size_t sleep_time);
int						table_init(t_table *table);
void					*philo_routine(void *arg);
void					clean_table(t_table *table);
size_t					time_ms_calc(void);
int						table_parse_args(t_table *table, int argc, char **argv);
#endif