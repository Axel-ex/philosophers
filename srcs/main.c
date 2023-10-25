/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:28:03 by achabrer          #+#    #+#             */
/*   Updated: 2023/10/24 22:05:45 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static	bool	start_routine(t_prog *p)
{
	int	i;

	p->start = get_time();
	i = 0;
	while (i < p->nb_philos)
	{
		if (pthread_create(&p->philos[i]->thread, NULL,
				routine, p->philos[i]))
			return (false);
		i++;
	}
	if (pthread_create(&p->monitor, NULL, monitor, p))
		return (false);
	//if (p->nb_philo != 1)
	return (true);
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
	exit_program(p);
}
