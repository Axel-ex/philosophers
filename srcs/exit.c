/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:02:03 by achabrer          #+#    #+#             */
/*   Updated: 2024/01/04 11:18:50 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	error_message(char *msg)
{
	printf("%sError:%s %s\n", RED, NC, msg);
	return (EXIT_FAILURE);
}

int	join_threads(t_prog *p)
{
	int	i;

	i = 0;
	while (i < p->nb_philos)
	{
		if (pthread_join(p->philos[i].thread, NULL))
			return (error_message("failed to join the thread"));
		i++;
	}
	if (p->nb_philos > 1)
		pthread_join(p->monitor, NULL);
	return (0);
}

void	destroy_mutexes(t_prog *p)
{
	int	i;

	i = -1;
	while (++i < p->nb_philos)
	{
		pthread_mutex_destroy(&p->forks[i]);
		pthread_mutex_destroy(&p->philos[i].philo_m);
	}
	pthread_mutex_destroy(&p->prog_m);
	pthread_mutex_destroy(&p->write_m);
}

void	exit_program(t_prog	*p)
{
	if (!p)
		return ;
	join_threads(p);
	destroy_mutexes(p);
	if (p->philos)
		free(p->philos);
	if (p->forks)
		free(p->forks);
	free(p);
}
