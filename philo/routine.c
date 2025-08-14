/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabsanto <sabsanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:16:22 by sabsanto          #+#    #+#             */
/*   Updated: 2025/08/14 01:30:25 by sabsanto         ###   ########.fr       */
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
	int	result;

	pthread_mutex_lock(&philo->data->mutex_death);
	result = philo->data->someone_died;
	pthread_mutex_unlock(&philo->data->mutex_death);
	return (result);
}

static int	try_eat(t_philo *philo)
{
	if (philo->data->philo_count == 1)
	{
		pthread_mutex_lock(philo->first_fork);
		print_action(philo, "has taken a fork");
		custom_sleep(philo->data->time_to_die + 1);
		pthread_mutex_unlock(philo->first_fork);
		return (1);
	}
	pthread_mutex_lock(philo->first_fork);
	print_action(philo, "has taken a fork");
	if (check_death_status(philo))
	{
		pthread_mutex_unlock(philo->first_fork);
		return (1);
	}
	pthread_mutex_lock(philo->second_fork);
	print_action(philo, "has taken a fork");
	if (check_death_status(philo))
	{
		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);
		return (1);
	}
	return (0);
}

static void	finish_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_meal);
	print_action(philo, "is eating");
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->mutex_meal);
	custom_sleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}


void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->data->philo_count == 1)
    {
        try_eat(philo); 
        return NULL;
    }

    if (philo->id % 2 == 0)
        custom_sleep(10);

    while (!check_death_status(philo))
    {
        if (try_eat(philo) == 0)
			finish_eating(philo);
		if (check_death_status(philo))
			break ;
		print_action(philo, "is sleeping");
		custom_sleep(philo->data->time_to_sleep);
		if (check_death_status(philo))
			break ;
		print_action(philo, "is thinking");
		if (philo->data->philo_count % 2 == 1)
			custom_sleep(1);
	}
    return NULL;
}
