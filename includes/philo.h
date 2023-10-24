/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:12:02 by achabrer          #+#    #+#             */
/*   Updated: 2023/10/24 14:31:57 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <time.h>

typedef struct s_prog	t_prog;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				time_ate;
	int				fork[2];
	pthread_mutex_t	meal_lock;
	time_t			last_meal;
	t_prog			*p;
}	t_philo;

typedef struct s_prog
{
	time_t			start;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				nb_philos;
	int				nb_meal;
	bool			stop;
	pthread_mutex_t	stop_m;
	pthread_mutex_t	write_m;
	pthread_mutex_t	*forks;
	t_philo			**philos;
}	t_prog;

//PARSE.C
int		parse_argv(int argc, char **argv);

//UTILS.C
int		ft_atoi(char *s);

//ROUTINE
void	*routine(void *data);

//INIT
t_prog	*init_program(int argc, char **argv);



#endif