/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:43:41 by achabrer          #+#    #+#             */
/*   Updated: 2024/01/03 15:13:10 by achabrer         ###   ########.fr       */
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

	gettimeofday(&curr_time, NULL);
	return ((curr_time.tv_sec * 1000) + (curr_time.tv_usec / 1000));
}

void	sleep_philo(t_prog *p, time_t sleep_time)
{
	time_t	wake_up;

	wake_up = get_time() + sleep_time;
	while (get_time() < wake_up)
	{
		if (is_finished(p))
			break ;
		usleep(100);
	}
}

void	write_status(t_philo *philo, t_status status, bool debug)
{
	long int	curr_time;
	char		*msg;

	if (is_finished(philo->p))
		return ;
	if (status == FORK1 || status == FORK2)
		msg = "has taken a fork";
	else if (status == EAT)
		msg = "is eating";
	else if (status == SLEEP)
		msg = "is sleeping";
	else if (status == THINK)
		msg = "is thinking";
	else if (status == DIED)
		msg = "died";
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

void	wait_threads(time_t start)
{
	while (get_time() < start)
		continue ;
}
