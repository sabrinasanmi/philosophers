/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabsanto <sabsanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:13:10 by sabsanto          #+#    #+#             */
/*   Updated: 2025/08/14 02:30:57 by sabsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
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

uint64_t	get_time(void)
{
	struct timeval	tv;
	uint64_t		ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}

uint64_t	get_relative_time(t_data *data)
{
	return (get_time() - data->start_time);
}

void	custom_sleep(uint64_t ms)
{
	uint64_t	start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(100);
}

void	clean_all(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->philo_count)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
	}
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mutex_meal);
	pthread_mutex_destroy(&data->mutex_death);
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
}
