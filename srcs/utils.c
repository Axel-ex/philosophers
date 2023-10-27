/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:43:41 by achabrer          #+#    #+#             */
/*   Updated: 2023/10/27 17:10:30 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(char *s)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
	while (*s == ' ' || *s == '\n')
		s++;
	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	while (*s == '+' || *s == '-')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		res *= 10;
		res += *s - '0';
		s++;
	}
	return (res * sign);
}

long	get_time(void)
{
	struct timeval	curr_time;
	long int		time;

	if (gettimeofday(&curr_time, NULL) != 0)
		return (0);
	time = (curr_time.tv_sec * 1000) + (curr_time.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start;

	start = get_time();
	while ((get_time() - start) < time_in_ms)
		usleep(time_in_ms / 10);
}

void	write_status(t_philo *philo, t_status status, int debug)
{
	long int	curr_time;
	char		*msg;

	if (status == FORK1 || status == FORK2)
		msg = "has taken a fork";
	else if (status == EAT)
		msg = "is eating";
	else if (status == SLEEP)
		msg = "is sleeping";
	else if (status == THINK)
		msg = "is thinking";
	else if (status == DIED)
		msg = "has died";
	pthread_mutex_lock(&philo->p->write_m);
	curr_time = get_time();
	if (!debug)
	{
		printf("%ld\t\t", curr_time - philo->p->start);
		printf(" %d %s\n", philo->id, msg);
	}
	else if (debug)
		write_status_debug(philo, status, msg);
	pthread_mutex_unlock(&philo->p->write_m);
}
