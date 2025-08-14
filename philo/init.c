/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabsanto <sabsanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:12:51 by sabsanto          #+#    #+#             */
/*   Updated: 2025/08/14 02:38:44 by sabsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			free(data->forks);
			data->forks = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->mutex_meal, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->mutex_print, NULL) != 0)
	{
		pthread_mutex_destroy(&data->mutex_meal);
		return (1);
	}
	if (pthread_mutex_init(&data->mutex_death, NULL) != 0)
	{
		pthread_mutex_destroy(&data->mutex_meal);
		pthread_mutex_destroy(&data->mutex_print);
		return (1);
	}
	return (0);
}

static void	init_basic_data(t_data *data, int argc, char **argv)
{
	data->philo_count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->meals_required = -1;
	if (argc == 6)
		data->meals_required = ft_atoi(argv[5]);
	data->someone_died = 0;
	data->start_time = get_time();
	data->forks = NULL;
	data->philos = NULL;
}

static int	finish_init(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philos)
	{
		clean_all(data);
		return (1);
	}
	init_philos(data);
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	if (check_args(argv))
		return (1);
	init_basic_data(data, argc, argv);
	if (validate_data(data, argc))
		return (1);
	if (init_mutexes(data))
		return (1);
	if (init_forks(data))
	{
		pthread_mutex_destroy(&data->mutex_meal);
		pthread_mutex_destroy(&data->mutex_print);
		pthread_mutex_destroy(&data->mutex_death);
		return (1);
	}
	return (finish_init(data));
}
