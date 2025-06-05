/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabsanto <sabsanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:12:51 by sabsanto          #+#    #+#             */
/*   Updated: 2025/06/03 17:24:45 by sabsanto         ###   ########.fr       */
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
			return (1);
		}
		i++;
	}
	return (0);
}

static void	init_philos(t_data *data)
{
	int	i;
	int left_fork, right_fork;

	i = 0;
	while (i < data->philo_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		
		pthread_mutex_lock(&data->mutex_meal);
		data->philos[i].last_meal = data->start_time;
		pthread_mutex_unlock(&data->mutex_meal);
		
		data->philos[i].data = data;
		
		// CORREÇÃO: Calcular índices dos garfos corretamente
		left_fork = i;
		right_fork = (i + 1) % data->philo_count;
		
		// Sempre pegar o garfo com menor índice primeiro para evitar deadlock
		if (left_fork < right_fork)
		{
			data->philos[i].first_fork = &data->forks[left_fork];
			data->philos[i].second_fork = &data->forks[right_fork];
		}
		else
		{
			data->philos[i].first_fork = &data->forks[right_fork];
			data->philos[i].second_fork = &data->forks[left_fork];
		}
		i++;
	}
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
	init_basic_data(data, argc, argv);
	
	// Inicializar mutexes primeiro
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
