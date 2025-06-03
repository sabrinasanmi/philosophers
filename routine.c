/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabsanto <sabsanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:16:22 by sabsanto          #+#    #+#             */
/*   Updated: 2025/06/03 17:08:24 by sabsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_action(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->mutex_print);
	pthread_mutex_lock(&philo->data->mutex_death);
	if (philo->data->someone_died == 0)
		printf("%lu %d %s\n", get_relative_time(philo->data), philo->id, msg);
	pthread_mutex_unlock(&philo->data->mutex_death);
	pthread_mutex_unlock(&philo->data->mutex_print);
}

static int	check_death_status(t_philo *philo)
{
	int result;
	
	pthread_mutex_lock(&philo->data->mutex_death);
	result = philo->data->someone_died;
	pthread_mutex_unlock(&philo->data->mutex_death);
	return (result);
}

static void	eat(t_philo *philo)
{
	// ORDEM PADRONIZADA - sempre pegar primeiro o garfo com menor índice
	pthread_mutex_lock(philo->first_fork);
	print_action(philo, "has taken a fork");
	
	if (check_death_status(philo))
	{
		pthread_mutex_unlock(philo->first_fork);
		return;
	}
	
	pthread_mutex_lock(philo->second_fork);
	print_action(philo, "has taken a fork");
	
	if (check_death_status(philo))
	{
		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);
		return;
	}
	
	// PROTEÇÃO DE ACESSO ÀS VARIÁVEIS COMPARTILHADAS
	pthread_mutex_lock(&philo->data->mutex_meal);
	print_action(philo, "is eating");
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->mutex_meal);
	
	custom_sleep(philo->data->time_to_eat);
	
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;

	// Stagger even philosophers to reduce contention
	if (philo->id % 2 == 0)
		custom_sleep(10);

	while (!check_death_status(philo))
	{
		eat(philo);

		if (check_death_status(philo))
			break;

		print_action(philo, "is sleeping");
		custom_sleep(philo->data->time_to_sleep);

		if (check_death_status(philo))
			break;

		print_action(philo, "is thinking");
		
		// Small thinking time to prevent busy waiting
		if (philo->data->philo_count % 2 == 1)
			custom_sleep(1);
	}
	return (NULL);
}
