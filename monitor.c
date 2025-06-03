/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabsanto <sabsanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:24:32 by sabsanto          #+#    #+#             */
/*   Updated: 2025/06/03 15:07:38 by sabsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_died(t_philo *philo)
{
	uint64_t	now;
	uint64_t	time_since_meal;

	now = get_time();
	pthread_mutex_lock(&philo->data->mutex_meal);
	time_since_meal = now - philo->last_meal;

	if (time_since_meal > philo->data->time_to_die)
	{
		philo->data->someone_died = 1;
		pthread_mutex_unlock(&philo->data->mutex_meal);
		pthread_mutex_lock(&philo->data->mutex_print);
		printf("%lu %d died\n", get_relative_time(philo->data), philo->id);
		pthread_mutex_unlock(&philo->data->mutex_print);
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

void	*monitor_death(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->philo_count)
		{
			if (philo_died(&data->philos[i]))
				return (NULL);
			i++;
		}
		if (all_ate_enough(data))
		{
			data->someone_died = 1;
			return (NULL);
		}
		usleep(500);
	}
}
