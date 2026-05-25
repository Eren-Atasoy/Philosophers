/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eratasoy <eratasoy@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 20:30:51 by eratasoy          #+#    #+#             */
/*   Updated: 2026/05/25 20:34:56 by eratasoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ignore_spaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] <= 13 && str[i] >= 9))
		i++;
	if (str[i] == '+')
		i++;
	return (i);
}

int	parse_positive_int(const char *str)
{
	long	sum;
	int		i;

	sum = 0;
	i = ignore_spaces(str);
	if (str[i] == '\0')
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		sum = sum * 10 + (str[i] - '0');
		if (sum > 2147483647)
			return (-1);
		i++;
	}
	if (sum <= 0)
		return (-1);
	return ((int)sum);
}

int	table_parse_args(t_table *table, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		write(2, "Error: ./philo philo_num die eat sleep [meals]\n", 47);
		return (0);
	}
	table->philo_count = parse_positive_int(argv[1]);
	table->time_to_die = parse_positive_int(argv[2]);
	table->time_to_eat = parse_positive_int(argv[3]);
	table->time_to_sleep = parse_positive_int(argv[4]);
	table->nb_times_to_eat = -1;
	if (argc == 6)
		table->nb_times_to_eat = parse_positive_int(argv[5]);
	if (table->philo_count == -1 || (long)table->time_to_die == -1
		|| (long)table->time_to_eat == -1 || (long)table->time_to_sleep == -1
		|| (argc == 6 && table->nb_times_to_eat == -1))
	{
		write(2, "Error: Invalid argument values.\n", 32);
		return (0);
	}
	return (1);
}
