/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabsanto <sabsanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:21:05 by sabsanto          #+#    #+#             */
/*   Updated: 2025/06/06 18:12:18 by sabsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	start_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_routine, &data->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

static void	wait_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

static int	run_simulation(t_data *data)
{
	pthread_t	monitor;

	if (start_threads(data) != 0)
	{
		printf("Erro ao criar threads dos filósofos.\n");
		return (1);
	}
	if (pthread_create(&monitor, NULL, monitor_death, data) != 0)
	{
		printf("Erro ao criar monitor.\n");
		data->someone_died = 1;
		wait_threads(data);
		return (1);
	}
	pthread_join(monitor, NULL);
	wait_threads(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		error;

	error = 0;
	if (argc < 5 || argc > 6)
		return (printf("Uso: ./philo n_phi t_die t_eat t_sleep [max_meals]\n"));
	if (init_data(&data, argc, argv) != 0)
	{
		printf("Erro na inicialização dos dados.\n");
		return (1);
	}
	error = run_simulation(&data);
	clean_all(&data);
	return (error);
}
