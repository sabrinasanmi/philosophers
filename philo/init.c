/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabsanto <sabsanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:12:51 by sabsanto          #+#    #+#             */
/*   Updated: 2025/08/13 20:18:35 by sabsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(const char *str)
{
	long	res;
	int		i;

	res = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		if (res > 2147483647)
			return (-1);
		i++;
	}
	return ((int)res);
}

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

static int	check_args(char **argv)
{
	int	i;
	int	j;
	int	value;

	i = 1;
	while (argv[i])
	{
		j = 0;
		if (!argv[i][0])
			return (1);
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		value = ft_atoi(argv[i]);
		if (value < 0)
			return (1);
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

int	init_data(t_data *data, int argc, char **argv)
{
	if (check_args(argv))
		return (1);
	init_basic_data(data, argc, argv);
	if (data->philo_count <= 0 || data->philo_count > 200)
		return (1);
	if (data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0)
		return (1);
	if (argc == 6 && data->meals_required <= 0)
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
	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philos)
	{
		clean_all(data);
		return (1);
	}
	init_philos(data);
	return (0);
}
