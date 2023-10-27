/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:23:30 by achabrer          #+#    #+#             */
/*   Updated: 2023/10/27 12:12:23 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// void	eat(t_philo *philo)
// {
// 	pthread_mutex_lock(philo->fork[LEFT]);

// }

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 != 0)
		ft_usleep(philo->p->time_to_sleep);
	while (!is_finished(philo->p))
	{
		write_message(philo, "is in routine...\n");
	}
	return (NULL);
}
