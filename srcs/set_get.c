/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:29:31 by achabrer          #+#    #+#             */
/*   Updated: 2023/10/28 13:37:24 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	getter(int philo_info, pthread_mutex_t *mutex)
{
	long	res;

	pthread_mutex_lock(mutex);
	res = (long)philo_info;
	pthread_mutex_unlock(mutex);
	return (res);
}

void	setter(long *to_set, long to_set_with, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	*to_set = to_set_with;
	pthread_mutex_unlock(mutex);
}
