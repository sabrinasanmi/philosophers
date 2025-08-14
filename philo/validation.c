/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabsanto <sabsanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:37:31 by sabsanto          #+#    #+#             */
/*   Updated: 2025/08/14 02:48:15 by sabsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char **argv)
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

int	validate_data(t_data *data, int argc)
{
	if (data->philo_count <= 0 || data->philo_count > 200)
		return (1);
	if (data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0)
		return (1);
	if (argc == 6 && data->meals_required <= 0)
		return (1);
	return (0);
}
