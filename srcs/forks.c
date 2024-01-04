/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:20:25 by achabrer          #+#    #+#             */
/*   Updated: 2024/01/04 11:50:10 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->p->forks[philo->fork[LEFT]]);
		write_status(philo, FORK1, DEBUG);
		pthread_mutex_lock(&philo->p->forks[philo->fork[RIGHT]]);
		write_status(philo, FORK2, DEBUG);
	}
	else
	{
		pthread_mutex_lock(&philo->p->forks[philo->fork[RIGHT]]);
		write_status(philo, FORK2, DEBUG);
		pthread_mutex_lock(&philo->p->forks[philo->fork[LEFT]]);
		write_status(philo, FORK1, DEBUG);
	}
}

void	drop_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->p->forks[philo->fork[LEFT]]);
	pthread_mutex_unlock(&philo->p->forks[philo->fork[RIGHT]]);
}
