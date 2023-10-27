/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:23:30 by achabrer          #+#    #+#             */
/*   Updated: 2023/10/27 18:42:38 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->p->forks[philo->fork[LEFT]]);
	write_status(philo, FORK1, DEBUG);
	pthread_mutex_lock(&philo->p->forks[philo->fork[RIGHT]]);
	write_status(philo, FORK2, DEBUG);
	ft_usleep(philo->p->time_to_eat);
	write_status(philo, EAT, DEBUG);
	pthread_mutex_unlock(&philo->p->forks[philo->fork[LEFT]]);
	pthread_mutex_unlock(&philo->p->forks[philo->fork[RIGHT]]);
	// pthread_mutex_lock(&philo->meal_lock);
	// philo->last_meal = get_time();
	// philo->time_ate++;
	// pthread_mutex_unlock(&philo->meal_lock);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 != 0)
		ft_usleep(philo->p->time_to_sleep);
	while (!is_finished(philo->p))
	{
		eat(philo);
		ft_usleep(philo->p->time_to_sleep);
	}
	return (NULL);
}
