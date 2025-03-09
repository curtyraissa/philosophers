/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcurty-g <rcurty-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:59:21 by rcurty-g          #+#    #+#             */
/*   Updated: 2025/03/05 18:00:09 by rcurty-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Assigns the left and right forks to each philosopher.
// Odd philosophers take forks `i-1` and `i`, while even philosophers
// take forks `i` and `i+1`. The last philosopher takes fork 0 as
// their right fork.
static void	init_forks(t_data *data, u_int64_t i)
{
	while (i < (data->total_p - 1))
	{
		if (i % 2)
		{
			data->philos[i].fork[LEFT] = &data->forks[i - 1];
			data->philos[i].fork[RIGHT] = &data->forks[i];
		}
		else
		{
			data->philos[i].fork[LEFT] = &data->forks[i];
			data->philos[i].fork[RIGHT] = &data->forks[i + 1];
		}
		i++;
	}
	if (i % 2)
	{
		data->philos[i].fork[LEFT] = &data->forks[i - 1];
		data->philos[i].fork[RIGHT] = &data->forks[i];
	}
	else
	{
		data->philos[i].fork[LEFT] = &data->forks[i];
		data->philos[i].fork[RIGHT] = &data->forks[0];
	}
}

// Initializes each philosopher's data, such as ID, number of meals,
// and death time. Initializes each philosopher's mutex.
static void	init_philos(t_data *data)
{
	u_int64_t	i;

	i = -1;
	while (++i < data->total_p)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].status = -1;
		data->philos[i].full = false;
		data->philos[i].death_t = data->death_t;
		pthread_mutex_init(&data->philos[i].lock, NULL);
	}
	init_forks(data, 0);
}

// Initializes the philosophers' threads and their mutexes.
static t_data	*init_threads(t_data *data)
{
	u_int64_t	i;

	data->finish = false;
	data->philos_full = 0;
	data->p_thread = malloc(data->total_p * sizeof(pthread_t));
	data->forks = malloc(data->total_p * sizeof(pthread_mutex_t));
	if (!data->p_thread || !data->forks)
		return (NULL);
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->log, NULL);
	pthread_mutex_init(&data->finish_lock, NULL);
	i = 0;
	while (i < data->total_p)
		pthread_mutex_init(&data->forks[i++], NULL);
	return (data);
}

// Initializes the global simulation data.
// Allocates memory for the `t_data` structure, assigns the values from
// the command line parameters, and initializes the threads and philosophers.
t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->total_p = ft_atol(av[1]);
	data->death_t = ft_atol(av[2]);
	data->eat_t = ft_atol(av[3]);
	data->sleep_time = ft_atol(av[4]);
	if (ac == 6)
		data->meals_needed = ft_atol(av[5]);
	else
		data->meals_needed = 0;
	if (!data->total_p || !data->death_t || !data->eat_t || !data->sleep_time)
	{
		free(data);
		return (NULL);
	}
	data->start_t = 0;
	data->philos = malloc(data->total_p * sizeof(t_philo));
	if (!data->philos)
		return (NULL);
	data = init_threads(data);
	init_philos(data);
	return (data);
}
