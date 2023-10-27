/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:34:21 by achabrer          #+#    #+#             */
/*   Updated: 2023/10/27 16:52:15 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	set_finished_flag(t_prog *p, bool value)
{
	pthread_mutex_lock(&p->stop_m);
	p->stop = value;
	pthread_mutex_unlock(&p->stop_m);
}

bool	is_finished(t_prog *p)
{
	int	res;

	res = false;
	pthread_mutex_lock(&p->stop_m);
	if (p->stop == true)
		res = true;
	pthread_mutex_unlock(&p->stop_m);
	return (res);
}

void	is_dead(t_prog *p)
{
	int		i;
	time_t	elapsed;
	time_t	curr_time;

	i = -1;
	curr_time = get_time();
	while (++i < p->nb_philos)
	{
		elapsed = curr_time - p->philos[i].last_meal;
		if (elapsed > p->time_to_die)
		{
			write_status(&p->philos[i], DIED, DEBUG);
			set_finished_flag(p, true);
		}
	}
}

void	all_full(t_prog *p)
{
	int		i;
	bool	all_full;

	i = -1;
	all_full = true;
	while (++i < p->nb_philos)
	{
		if (p->philos[i].time_ate < p->nb_meal)
			all_full = false;
	}
	if (all_full)
		set_finished_flag(p, true);
}

void	*monitor(void *data)
{
	t_prog	*p;

	p = (t_prog *)data;
	if (p->nb_meal == 0)
		return (NULL);
	//wait for threads
	while (!is_finished(p))
	{
		is_dead(p);
		all_full(p);
	}
	return (NULL);
}
