/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:12:02 by achabrer          #+#    #+#             */
/*   Updated: 2023/10/28 14:57:19 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

# define NC		"\e[0m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"

# ifndef DEBUG
#  define DEBUG false
# endif

# define STD_ERR_USAGE "Usage: <number of philo> <time to die> <time to sleep>\
 <time to think> <nb of meal>"

typedef enum s_status
{
	FORK1,
	FORK2,
	EAT,
	SLEEP,
	THINK,
	DIED,
}	t_status;

typedef enum s_fork
{
	LEFT = 0,
	RIGHT = 1,
}	t_fork;

typedef struct s_prog	t_prog;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				fork[2];
	long			time_ate;
	time_t			last_meal;
	pthread_mutex_t	philo_m;
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
	pthread_mutex_t	prog_m;
	pthread_mutex_t	write_m;
	pthread_mutex_t	*forks;
	pthread_t		monitor;
	t_philo			*philos;
}	t_prog;

//PARSE.C
int			parse_argv(int argc, char **argv);

//UTILS.C
int			ft_atoi(char *s);
long		get_time(void);
void		ft_usleep(long int time_in_ms);
void		write_status(t_philo *philo, t_status status, bool debug);
long		getter(int philo_info, pthread_mutex_t *mutex);

//ROUTINE
void		*routine(void *data);

//INIT
t_prog		*init_program(int argc, char **argv);

//MONITOR
void		*monitor(void *data);

//EXIT.c
void		exit_program(t_prog	*p);
int			error_message(char *msg);


bool		is_finished(t_prog *p);
//DEBUG.C
void		write_status_debug(t_philo *philo, t_status status, char *msg);

//SET_GET.C
void		setter(long *to_set, long to_set_with, pthread_mutex_t *mutex);

#endif