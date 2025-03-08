/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcurty-g <rcurty-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:59:15 by rcurty-g          #+#    #+#             */
/*   Updated: 2025/03/03 15:36:46 by rcurty-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// If the philosopher is not dead and is not sleeping,
// the function sets him to "sleeping" state, logs it,
// and makes the philosopher sleep for the determined time.
void	sleeping(t_philo *philo)
{
	if (!is_dead(philo) && philo->status != SLEEPING)
	{
		philo->status = SLEEPING;
		logs(philo, philo->status);
		usleep_time(philo, philo->data->sleep_time);
	}
}

// If the philosopher is not dead and is not thinking,
// the function sets him to "thinking" state, logs it,
// and makes the philosopher think for the defined time (5 ms).
void	thinking(t_philo *philo)
{
	if (!is_dead(philo) && philo->status != THINKING)
	{
		philo->status = THINKING;
		logs(philo, philo->status);
		usleep_time(philo, 5);
	}
}

// Tries to pick the specified fork (left or right).
// If the philosopher is not dead, the fork is picked,
// and the status is logged.
static bool	get_fork(t_philo *philo, int fork)
{
	pthread_mutex_lock(philo->fork[fork]);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(philo->fork[fork]);
		return (false);
	}
	logs(philo, FORK);
	return (true);
}

// Tries to pick both forks (left and right).
static bool	get_forks(t_philo *philo)
{
	if (!get_fork(philo, LEFT))
		return (false);
	if (!get_fork(philo, RIGHT))
	{
		pthread_mutex_unlock(philo->fork[LEFT]);
		return (false);
	}
	return (true);
}

// If it successfully picks both forks, it starts the eating process,
// updates the status to "eating", logs the action,
// pauses for the required time, and increments the meal counter.
void	eating(t_philo *philo)
{
	if (!get_forks(philo))
		return ;
	pthread_mutex_lock(&philo->lock);
	philo->death_t = get_time() + philo->data->death_t;
	pthread_mutex_unlock(&philo->lock);
	philo->status = EATING;
	logs(philo, philo->status);
	philo->meals_eaten++;
	usleep_time(philo, philo->data->eat_t);
	pthread_mutex_unlock(philo->fork[LEFT]);
	pthread_mutex_unlock(philo->fork[RIGHT]);
}
