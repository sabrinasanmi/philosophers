/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabsanto <sabsanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:21:10 by sabsanto          #+#    #+#             */
/*   Updated: 2025/06/03 14:52:25 by sabsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdint.h>

// Forward declaration
typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

// Structs

struct s_data
{
	int				philo_count;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				meals_required;
	int				someone_died;
	uint64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_meal;
	t_philo			*philos;
};

struct s_philo
{
	int				id;
	int				meals_eaten;
	uint64_t		last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
};

// Init (init.c)
int			init_data(t_data *data, int argc, char **argv);

// Routine (routine.c)
void		*philo_routine(void *arg);

// Monitor (monitor.c)
void		*monitor_death(void *arg);

// Utils (utils.c)
uint64_t	get_time(void);
uint64_t	get_relative_time(t_data *data);
void		custom_sleep(uint64_t ms);
void		clean_all(t_data *data);

#endif