/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:28:03 by achabrer          #+#    #+#             */
/*   Updated: 2023/10/27 17:14:29 by achabrer         ###   ########.fr       */
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
		if (pthread_create(&p->philos[i].thread, NULL,
				routine, &p->philos[i]))
			return (false);
		p->philos[i].last_meal = p->start;
		i++;
	}
	if (pthread_create(&p->monitor, NULL, monitor, p))
		return (false);
	return (true);
}

int	main(int argc, char **argv)
{
	t_prog	*p;

	if (parse_argv(argc, argv))
		return (EXIT_FAILURE);
	p = init_program(argc, argv);
	if (!p)
		return (error_message("Program initialization failed"));
	if (!start_routine(p))
		return (error_message("Routine failed to start"));
	exit_program(p);
	return (EXIT_SUCCESS);
}
