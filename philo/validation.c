/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcurty-g <rcurty-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:59:18 by rcurty-g          #+#    #+#             */
/*   Updated: 2025/03/17 11:12:33 by rcurty-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Checks if the philosopher has reached the required number of meals.
static void	is_full(t_philo	*philo)
{
	if (philo->meals_eaten >= philo->data->meals_needed
		&& philo->data->meals_needed != 0 && !philo->full)
	{
		philo->data->philos_full++;
		philo->full = true;
	}
}

// Checks if the philosopher has died or if the simulation has ended.
bool	is_dead(t_philo *philo)
{
	bool	dead;

	dead = false;
	pthread_mutex_lock(&philo->lock);
	pthread_mutex_lock(&philo->data->finish_lock);
	if (get_time() >= philo->death_t || philo->data->finish)
	{
		if (!philo->data->finish)
			logs(philo, DEATH);
		philo->data->finish = true;
	}
	pthread_mutex_lock(&philo->data->lock);
	is_full(philo);
	if (philo->data->philos_full == philo->data->total_p)
		philo->data->finish = true;
	dead = philo->data->finish;
	pthread_mutex_unlock(&philo->data->lock);
	pthread_mutex_unlock(&philo->data->finish_lock);
	pthread_mutex_unlock(&philo->lock);
	return (dead);
}

// Checks if there is only one philosopher in the simulation.
bool	is_alone(t_philo *philo)
{
	if (philo->data->total_p == 1)
	{
		pthread_mutex_lock(philo->fork[RIGHT]);
		logs(philo, FORK);
		pthread_mutex_unlock(philo->fork[RIGHT]);
		logs(philo, THINKING);
		while (!is_dead(philo))
			usleep(1000);
		return (true);
	}
	return (false);
}

// Validates the parameters passed through the command line.
int	validate_arguments(char **av)
{
	int		i;
	int		j;
	long	tmp;

	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
		{
			if (av[i][j] == '-')
				return (1);
			if (av[i][j] == '+')
				j++;
			if (av[i][j] && (av[i][j] < '0' || av[i][j] > '9'))
				return (1);
		}
		tmp = ft_atol(av[i]);
		if (tmp < 0 || tmp > 4294967295)
			return (1);
	}
	if (av[2][0] == '0' && !av[2][1])
		return (1);
	return (0);
}
