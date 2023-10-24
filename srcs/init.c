/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:34:42 by achabrer          #+#    #+#             */
/*   Updated: 2023/10/24 14:46:01 by achabrer         ###   ########.fr       */
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

static void	assign_forks(t_philo *philo)
{
	philo->fork[0] = philo->id;
	philo->fork[1] = (philo->id + 1) % philo->p->nb_philos;
	if (philo->id % 2)
	{
		philo->fork[0] = (philo->id + 1) % philo->p->nb_philos;
		philo->fork[1] = philo->id;
	}
}

static t_philo	**init_philos(t_prog *p)
{
	t_philo	**philos;
	int		i;


	philos = malloc(sizeof(t_philo) * p->nb_philos);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < p->nb_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
			return (NULL);
		if (pthread_mutex_init(&philos[i]->meal_lock, NULL))
			return (NULL);
		philos[i]->id = i + 1;
		philos[i]->last_meal = 0;
		philos[i]->time_ate = 0;
		philos[i]->p = p;
		assign_forks(philos[i]);
		i++;
	}
	return (philos);
}

int	init_mutexes(t_prog *p)
{
	p->forks = init_forks(p);
	if (!p->forks)
		return (-1);
	if (pthread_mutex_init(&p->stop_m, NULL))
		return (-1);
	if (pthread_mutex_init(&p->write_m, NULL))
		return (-1);
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
	p->philos = init_philos(p);
	if (!p->philos)
		return (NULL);
	if (init_mutexes(p))
		return (NULL);
	return (p);
}

