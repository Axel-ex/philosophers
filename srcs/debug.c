/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:34:16 by achabrer          #+#    #+#             */
/*   Updated: 2023/10/27 17:09:23 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	write_status_debug(t_philo *philo, t_status status, char *msg)
{
	char	*color;

	if (status == EAT)
		color = GREEN;
	else if (status == DIED)
		color = RED;
	printf("%ld\t\t", get_time() - philo->p->start);
	if (status == FORK1)
		printf("%d has taken left fork:\t%sfork[%d]%s\n", philo->id,
			PURPLE, philo->fork[LEFT], NC);
	else if (status == FORK2)
		printf("%d has taken right fork:\t%sfork[%d]%s\n", philo->id,
			PURPLE, philo->fork[RIGHT], NC);
	else
		printf("%s%d %s%s\n", color, philo->id, msg, NC);
}
