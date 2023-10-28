/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:34:21 by achabrer          #+#    #+#             */
/*   Updated: 2023/10/28 16:00:37 by achabrer         ###   ########.fr       */
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
	return (getter(p->stop, &p->prog_m));
}

void	is_dead(t_prog *p)
{
	int		i;
	time_t	elapsed;
	time_t	curr_time;

	i = -1;
	curr_time = get_time();
	while (++i < getter(p->nb_philos, &p->prog_m))
	{
		elapsed = curr_time - getter(p->philos[i].last_meal, &p->philos[i].philo_m);
		if (elapsed > getter(p->time_to_die, &p->prog_m) && !is_finished(p))
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
	while (++i < getter(p->nb_philos, &p->prog_m))
	{
		if (getter(p->philos[i].time_ate, &p->philos[i].philo_m)
			< getter(p->nb_meal, &p->prog_m))
			all_full = false;
	}
	if (all_full && !is_finished(p))
		set_finished_flag(p, true);
}

void	*monitor(void *data)
{
	t_prog	*p;

	p = (t_prog *)data;
	if (p->nb_meal == 0)
		return (NULL);
	ft_usleep(p->time_to_die);
	while (!is_finished(p))
	{
		is_dead(p);
		all_full(p);
	}
	return (NULL);
}
