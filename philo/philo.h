/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcurty-g <rcurty-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:40:36 by rcurty-g          #+#    #+#             */
/*   Updated: 2025/03/05 10:20:56 by rcurty-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// LIBRARIES

# include <stdio.h> // printf
# include <pthread.h> // pthread_create(), pthread_mutex_lock()
# include <sys/time.h> // gettimeofday()
# include <stdlib.h> // malloc() e free()
# include <unistd.h> // usleep()
# include <stdbool.h> // bool, true, false

// ENUMERATED CONSTANTS

enum e_forks
{
	LEFT,
	RIGHT,
};

enum e_actions
{
	DEATH,
	EATING,
	SLEEPING,
	THINKING,
	FORK,
	FULL
};

// STRUCTS

struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	u_int64_t		id;
	u_int64_t		meals_eaten;
	u_int64_t		death_t;
	int				status;
	bool			full;
	pthread_mutex_t	lock;
	pthread_mutex_t	*fork[2];
}					t_philo;

typedef struct s_data
{
	pthread_t		*p_thread;
	t_philo			*philos;
	u_int64_t		total_p;
	u_int64_t		death_t;
	u_int64_t		eat_t;
	u_int64_t		sleep_time;
	u_int64_t		meals_needed;
	u_int64_t		start_t;
	u_int64_t		philos_full;
	bool			finish;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	log;
	pthread_mutex_t	finish_lock;
}					t_data;

// FUNCTION PROTOTYPES

void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);

int			validate_arguments(char **av);
bool		is_alone(t_philo *philo);
bool		is_dead(t_philo *philo);

void		*behavior(void *philo_ptr);
void		logs(t_philo *p, int status);

u_int64_t	get_time(void);
void		usleep_time(t_philo *philo, u_int64_t time);
long		ft_atol(const char *str);
void		free_data(t_data *data);

t_data		*init_data(int ac, char **av);

#endif
