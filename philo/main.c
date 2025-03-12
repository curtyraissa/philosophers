/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcurty-g <rcurty-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:59:23 by rcurty-g          #+#    #+#             */
/*   Updated: 2025/03/05 09:34:04 by rcurty-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Initializes the simulation by creating threads for each philo
// and waits for all threads to finish their execution.
// Uses mutexes to ensure safe access to global data.
static int	start_simulation(t_data *data)
{
	u_int64_t	n;

	data->start_t = get_time();
	if (data->start_t == 0)
		return (1);
	pthread_mutex_lock(&data->lock);
	n = 0;
	while (n < data->total_p)
	{
		if (pthread_create(&data->p_thread[n], NULL, &behavior,
				&data->philos[n]))
			return (1);
		n++;
	}
	pthread_mutex_unlock(&data->lock);
	n = 0;
	while (n < data->total_p)
	{
		if (pthread_join(data->p_thread[n], NULL))
			return (1);
		n++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data		*data;

	if ((ac != 5 && ac != 6) || validate_arguments(av))
	{
		printf("Error: Invalid arguments\n");
		return (0);
	}
	data = init_data(ac, av);
	if (!data)
	{
		free_data(data);
		return (1);
	}
	start_simulation(data);
	free_data(data);
	return (0);
}
