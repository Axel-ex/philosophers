/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:23:30 by achabrer          #+#    #+#             */
/*   Updated: 2023/10/28 15:48:50 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eat_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->p->forks[philo->fork[LEFT]]);
	write_status(philo, FORK1, DEBUG);
	pthread_mutex_lock(&philo->p->forks[philo->fork[RIGHT]]);
	write_status(philo, FORK2, DEBUG);
	ft_usleep(philo->p->time_to_eat);
	write_status(philo, EAT, DEBUG);
	pthread_mutex_unlock(&philo->p->forks[philo->fork[LEFT]]);
	pthread_mutex_unlock(&philo->p->forks[philo->fork[RIGHT]]);
	setter(&philo->last_meal, get_time(), &philo->philo_m);
	if (!is_finished(philo->p))
		setter(&philo->time_ate, philo->time_ate++, &philo->philo_m);
	ft_usleep(philo->p->time_to_sleep);
	write_status(philo, SLEEP, DEBUG);
}

// void	think(t_philo *philo)
// {

// }

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 != 0)
		ft_usleep(philo->p->time_to_sleep);
	while (!is_finished(philo->p))
	{
		eat_sleep(philo);
		ft_usleep(philo->p->time_to_sleep);
	}
	return (NULL);
}
