/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcurty-g <rcurty-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:59:29 by rcurty-g          #+#    #+#             */
/*   Updated: 2025/03/06 12:00:18 by rcurty-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Pauses execution.
// Adjusts the wait time to prevent the philosopher from dying prematurely.
void	usleep_time(t_philo *philo, u_int64_t time)
{
	u_int64_t	current_time;

	current_time = get_time();
	if ((current_time + time) >= philo->death_t)
		usleep((philo->death_t - current_time) * 1000);
	else
		usleep(time * 1000);
}

// Gets the current time in milliseconds
u_int64_t	get_time(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL))
	{
		printf("ERROR: gettimeofday()");
		return (0);
	}
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

// Converts a string to a integer
long	ft_atol(const char *str)
{
	long	sign;
	long	res;

	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}

// Frees allocated memory and destroys mutexes
void	free_data(t_data *data)
{
	u_int64_t	i;

	if (!data)
		return ;
	i = -1;
	while (++i < data->total_p)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].lock);
	}
	pthread_mutex_destroy(&data->lock);
	pthread_mutex_destroy(&data->log);
	pthread_mutex_destroy(&data->finish_lock);
	if (data->p_thread)
		free(data->p_thread);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	free(data);
}
