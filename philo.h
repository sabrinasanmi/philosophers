/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabsanto <sabsanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:21:10 by sabsanto          #+#    #+#             */
/*   Updated: 2025/06/03 17:12:41 by sabsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdint.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	uint64_t		last_meal;
	pthread_mutex_t	*first_fork;  // Sempre o garfo com menor índice
	pthread_mutex_t	*second_fork; // Sempre o garfo com maior índice
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				philo_count;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				meals_required;
	int				someone_died;
	uint64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex_meal;   // Protege last_meal e meals_eaten
	pthread_mutex_t	mutex_print;  // Protege printf
	pthread_mutex_t	mutex_death;  // Protege someone_died
	t_philo			*philos;
}	t_data;

// Function prototypes
int			init_data(t_data *data, int argc, char **argv);
void		*philo_routine(void *arg);
void		*monitor_death(void *arg);
uint64_t	get_time(void);
uint64_t	get_relative_time(t_data *data);
void		custom_sleep(uint64_t ms);
void		clean_all(t_data *data);

#endif