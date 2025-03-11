/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behavior.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcurty-g <rcurty-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:59:26 by rcurty-g          #+#    #+#             */
/*   Updated: 2025/03/11 12:53:31 by rcurty-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Logs the actions of each philosopher, 
// with the time elapsed since the start of the simulation.
void	logs(t_philo *p, int status)
{
	pthread_mutex_lock(&p->data->log);
	if (status == DEATH)
		printf("%lu %lu died\n", get_time() - p->data->start_t, p->id);
	else if (status == EATING)
		printf("%lu %lu is eating\n", get_time() - p->data->start_t, p->id);
	else if (status == SLEEPING)
		printf("%lu %lu is sleeping\n", get_time() - p->data->start_t, p->id);
	else if (status == THINKING)
		printf("%lu %lu is thinking\n", get_time() - p->data->start_t, p->id);
	else if (status == FORK)
		printf("%lu %lu has taken a fork\n",
			get_time() - p->data->start_t, p->id);
	pthread_mutex_unlock(&p->data->log);
}

// Defines the philosopher's main actions, alternating between eating,
// sleeping and thinking. The simulation ends when the philosopher dies
// or reaches the required number of meals.
void	*behavior(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	pthread_mutex_lock(&philo->lock);
	philo->death_t = philo->data->start_t + philo->data->death_t;
	pthread_mutex_unlock(&philo->lock);
	if (philo->id % 2 == 0 || philo->id == philo->data->total_p)
		thinking(philo);
	if (is_alone(philo))
		return (NULL);
	while (!is_dead(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
