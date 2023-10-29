/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:34:42 by achabrer          #+#    #+#             */
/*   Updated: 2023/10/29 13:24:53 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static pthread_mutex_t	*init_forks(t_prog *p)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * p->nb_philos);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < p->nb_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (NULL);
		i++;
	}
	return (forks);
}

static void	assign_forks(t_philo *philo, int index)
{
	philo->fork[LEFT] = philo->id - 1;
	if (index == philo->p->nb_philos - 1)
		philo->fork[RIGHT] = 0;
	else
		philo->fork[RIGHT] = philo->id;
}

static t_philo	*init_philos(t_prog *p)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)malloc(sizeof(t_philo) * p->nb_philos);
	if (!philos)
		return (NULL);
	i = -1;
	while (++i < p->nb_philos)
	{
		if (pthread_mutex_init(&philos[i].philo_m, NULL))
		{
			error_message("Failed to init philo mutexes.\n");
			return (NULL);
		}
		philos[i].id = i + 1;
		philos[i].last_meal = 0;
		philos[i].time_ate = 0;
		philos[i].p = p;
		assign_forks(&philos[i], i);
	}
	return (philos);
}

int	init_mutexes(t_prog *p)
{
	p->forks = init_forks(p);
	if (!p->forks)
		return (error_message("failed to init the forks."));
	if (pthread_mutex_init(&p->prog_m, NULL))
		return (error_message("failed to init program mutex"));
	if (pthread_mutex_init(&p->write_m, NULL))
		return (error_message("failed to init write mutex"));
	return (0);
}

t_prog	*init_program(int argc, char **argv)
{
	t_prog	*p;

	p = (t_prog *)malloc(sizeof(t_prog));
	if (!p)
		return (NULL);
	p->nb_philos = ft_atoi(argv[1]);
	p->time_to_die = ft_atoi(argv[2]);
	p->time_to_eat = ft_atoi(argv[3]);
	p->time_to_sleep = ft_atoi(argv[4]);
	p->nb_meal = -1;
	p->stop = false;
	if (argc - 1 == 5)
		p->nb_meal = ft_atoi(argv[5]);
	if (init_mutexes(p))
		return (NULL);
	p->philos = init_philos(p);
	if (!p->philos)
		return (NULL);
	return (p);
}
