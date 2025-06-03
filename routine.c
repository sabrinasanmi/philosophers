/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabsanto <sabsanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:16:22 by sabsanto          #+#    #+#             */
/*   Updated: 2025/06/03 15:18:34 by sabsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include "philo.h"

static void	print_action(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->mutex_print);
	if (philo->data->someone_died == 0)
		printf("%lu %d %s\n", get_relative_time(philo->data), philo->id, msg);
	pthread_mutex_unlock(&philo->data->mutex_print);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(philo->left_fork);
		return;
	}
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, "has taken a fork");
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return;
	}
	pthread_mutex_lock(&philo->data->mutex_meal);
	print_action(philo, "is eating");
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->mutex_meal);
	custom_sleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;

	if (philo->id % 2 == 0)
		custom_sleep(10);  // delay mais preciso

	while (philo->data->someone_died == 0)
	{
		eat(philo);

		if (philo->data->someone_died)
			break;

		print_action(philo, "is sleeping");
		custom_sleep(philo->data->time_to_sleep);

		if (philo->data->someone_died)
			break;

		print_action(philo, "is thinking");
	}
	return (NULL);
}
