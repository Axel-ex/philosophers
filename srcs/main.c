/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:28:03 by achabrer          #+#    #+#             */
/*   Updated: 2023/10/24 14:47:53 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static	bool	start_routine(t_prog *p)
{
	int	i;

	i = 0;
	while (i < p->nb_philos)
	{
		if (pthread_create(&p->philos[i]->thread, NULL,
				routine, p->philos[i]))
			return (false);
		i++;
	}
	return (true);
}

int	join_threads(t_prog *p)
{
	int	i;

	i = 0;
	while (i < p->nb_philos)
	{
		if (pthread_join(p->philos[i]->thread, NULL))
		{
			printf("failed to join.\n");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_prog	*p;

	if (parse_argv(argc, argv))
		return (-1);
	p = init_program(argc, argv);
	if (!p)
		return (-1);
	if (!start_routine(p))
		return (-1);
	join_threads(p);
}
