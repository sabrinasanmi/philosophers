/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabsanto <sabsanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:24:32 by sabsanto          #+#    #+#             */
/*   Updated: 2025/06/06 22:06:15 by sabsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_print);
	printf("%lu %d died\n", get_relative_time(philo->data), philo->id);
	pthread_mutex_unlock(&philo->data->mutex_print);
}

static int	philo_died(t_philo *philo)
{
	uint64_t	now;
	uint64_t	time_since_meal;
	int			died;

	died = 0;
	now = get_time();
	pthread_mutex_lock(&philo->data->mutex_meal);
	time_since_meal = now - philo->last_meal;
	if (time_since_meal > philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->mutex_death);
		if (philo->data->someone_died == 0)
		{
			philo->data->someone_died = 1;
			died = 1;
		}
		pthread_mutex_unlock(&philo->data->mutex_death);
		if (died)
			print_death(philo);
		pthread_mutex_unlock(&philo->data->mutex_meal);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex_meal);
	return (0);
}

static int	all_ate_enough(t_data *data)
{
	int	i;
	int	satisfied;

	if (data->meals_required == -1)
		return (0);
	satisfied = 0;
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->mutex_meal);
		if (data->philos[i].meals_eaten >= data->meals_required)
			satisfied++;
		pthread_mutex_unlock(&data->mutex_meal);
		i++;
	}
	return (satisfied == data->philo_count);
}

static int	check_death_flag(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->mutex_death);
	result = data->someone_died;
	pthread_mutex_unlock(&data->mutex_death);
	return (result);
}

void	*monitor_death(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!check_death_flag(data))
	{
		i = 0;
		while (i < data->philo_count && !check_death_flag(data))
		{
			if (philo_died(&data->philos[i]))
				return (NULL);
			i++;
		}
		if (all_ate_enough(data))
		{
			pthread_mutex_lock(&data->mutex_death);
			data->someone_died = 1;
			pthread_mutex_unlock(&data->mutex_death);
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}
