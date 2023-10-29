/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:34:21 by achabrer          #+#    #+#             */
/*   Updated: 2023/10/29 13:10:30 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	set_finished_flag(t_prog *p, bool value)
{
	pthread_mutex_lock(&p->prog_m);
	p->stop = value;
	pthread_mutex_unlock(&p->prog_m);
}

bool	is_finished(t_prog *p)
{
	bool	res;

	res = false;
	pthread_mutex_lock(&p->prog_m);
	if (p->stop)
		res = true;
	pthread_mutex_unlock(&p->prog_m);
	return (res);
}

bool	is_dead(t_philo *philo)
{
	time_t	elapsed;

	elapsed = get_time() - philo->last_meal;
	if (elapsed > philo->p->time_to_die)
	{
		write_status(philo, DIED, DEBUG);
		set_finished_flag(philo->p, true);
		pthread_mutex_unlock(&philo->philo_m);
		return (true);
	}
	return (false);
}

bool	end_of_routine(t_prog *p)
{
	int		i;
	bool	all_full;

	i = -1;
	all_full = true;
	while (++i < p->nb_philos)
	{
		pthread_mutex_lock(&p->philos[i].philo_m);
		if (is_dead(&p->philos[i]))
		{
			set_finished_flag(p, true);
			return (true);
		}
		if (p->nb_meal != -1 && p->philos[i].time_ate
			<= p->nb_meal)
			all_full = false;
		pthread_mutex_unlock(&p->philos[i].philo_m);
	}
	if (p->nb_meal != -1 && all_full)
	{
		set_finished_flag(p, true);
		return (true);
	}
	return (false);
}

void	*monitor(void *data)
{
	t_prog	*p;

	p = (t_prog *)data;
	if (p->nb_meal == 0)
		return (NULL);
	wait_threads(p->start);
	while (!end_of_routine(p))
		ft_usleep(100);
	return (NULL);
}
