/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabsanto <sabsanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 21:39:32 by sabsanto          #+#    #+#             */
/*   Updated: 2025/06/06 22:09:27 by sabsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo_basic(t_philo *philo, int id, t_data *data)
{
	philo->id = id + 1;
	philo->meals_eaten = 0;
	philo->data = data;
	pthread_mutex_lock(&data->mutex_meal);
	philo->last_meal = data->start_time;
	pthread_mutex_unlock(&data->mutex_meal);
}

static void	assign_forks(t_philo *philo, int left, int right, t_data *data)
{
	if (left < right)
	{
		philo->first_fork = &data->forks[left];
		philo->second_fork = &data->forks[right];
	}
	else
	{
		philo->first_fork = &data->forks[right];
		philo->second_fork = &data->forks[left];
	}
}

void	init_philos(t_data *data)
{
	int	i;
	int	left_fork;
	int	right_fork;

	i = 0;
	while (i < data->philo_count)
	{
		init_philo_basic(&data->philos[i], i, data);
		left_fork = i;
		right_fork = (i + 1) % data->philo_count;
		assign_forks(&data->philos[i], left_fork, right_fork, data);
		i++;
	}
}
