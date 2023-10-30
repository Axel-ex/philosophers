/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:23:30 by achabrer          #+#    #+#             */
/*   Updated: 2023/10/30 11:46:50 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	think(t_philo *philo)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->philo_m);
	time_to_think = (philo->p->time_to_die
			- (get_time() - philo->last_meal)
			- philo->p->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->philo_m);
	if (time_to_think < 0)
		time_to_think = 0;
	write_status(philo, THINK, DEBUG);
	sleep_philo(philo->p, time_to_think);
}

static void	eat_sleep_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->p->forks[philo->fork[LEFT]]);
	write_status(philo, FORK1, DEBUG);
	pthread_mutex_lock(&philo->p->forks[philo->fork[RIGHT]]);
	write_status(philo, FORK2, DEBUG);
	pthread_mutex_lock(&philo->philo_m);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->philo_m);
	write_status(philo, EAT, DEBUG);
	sleep_philo(philo->p, philo->p->time_to_eat);
	pthread_mutex_lock(&philo->philo_m);
	philo->time_ate++;
	pthread_mutex_unlock(&philo->philo_m);
	pthread_mutex_unlock(&philo->p->forks[philo->fork[LEFT]]);
	pthread_mutex_unlock(&philo->p->forks[philo->fork[RIGHT]]);
	sleep_philo(philo->p, philo->p->time_to_sleep);
	write_status(philo, SLEEP, DEBUG);
}

static void	philo_alone(t_philo *philo)
{
	write_status(philo, FORK1, DEBUG);
	sleep_philo(philo->p, philo->p->time_to_die);
	write_status(philo, DIED, DEBUG);
}


void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_threads(philo->p->start);
	if (philo->p->nb_philos == 1)
	{
		philo_alone(philo);
		return (NULL);
	}
	if (philo->id % 2)
		think(philo);
	while (!is_finished(philo->p))
	{
		eat_sleep_think(philo);
		think(philo);
	}
	return (NULL);
}
