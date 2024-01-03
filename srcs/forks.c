/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:20:25 by achabrer          #+#    #+#             */
/*   Updated: 2024/01/03 14:48:15 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->p->forks[philo->fork[LEFT]]);
	write_status(philo, FORK1, DEBUG);
	pthread_mutex_lock(&philo->p->forks[philo->fork[RIGHT]]);
	write_status(philo, FORK2, DEBUG);
	return (true);
}

void	drop_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->p->forks[philo->fork[LEFT]]);
	pthread_mutex_unlock(&philo->p->forks[philo->fork[RIGHT]]);
}