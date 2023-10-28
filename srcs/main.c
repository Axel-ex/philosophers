/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:28:03 by achabrer          #+#    #+#             */
/*   Updated: 2023/10/28 15:49:48 by achabrer         ###   ########.fr       */
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
		setter(&p->philos[i].last_meal, p->start, &p->philos[i].philo_m);
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
		return (error_message(STD_ERR_USAGE));
	p = init_program(argc, argv);
	if (!p)
		return (error_message("Program initialization failed"));
	if (!start_routine(p))
		return (error_message("Routine failed to start"));
	exit_program(p);
	return (EXIT_SUCCESS);
}
