/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:02:03 by achabrer          #+#    #+#             */
/*   Updated: 2023/10/24 15:29:01 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*error_msg(char *msg)
{
	printf("Error: %s", msg);
	return (NULL);
}

void	*join_threads(t_prog *p)
{
	int	i;

	i = 0;
	while (i < p->nb_philos)
	{
		if (pthread_join(p->philos[i]->thread, NULL))
			return (error_msg("failed to join the thread"));
		i++;
	}
	return (p);
}

void	destroy_mutexes(t_prog *p)
{
	int	i;

	i = -1;
	while (++i < p->nb_philos)
		pthread_mutex_destroy(&p->forks[i]);
	pthread_mutex_destroy(&p->stop_m);
	pthread_mutex_destroy(&p->write_m);
}

void	free_prog(t_prog *p)
{
	int	i;

	if (!p)
		return ;
	i = -1;
	if (p->philos)
	{
		while (++i < p->nb_philos)
			free(p->philos[i]);
		free(p->philos);
	}
	if (p->forks)
		free(p->forks);
	free(p);
}

void	exit_program(t_prog	*p)
{
	join_threads(p);
	destroy_mutexes(p);
	free_prog(p);
}
