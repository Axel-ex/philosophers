/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:12:02 by achabrer          #+#    #+#             */
/*   Updated: 2024/01/03 14:38:16 by achabrer         ###   ########.fr       */
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
	time_t			time_ate;
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

/// ============================================================================
// PARSE.C
// =============================================================================
/**
 * @brief Checks if argv contains only non zero numeric values.
 * 
 * @param argc 
 * @param argv 
 * @return int 0 if success
 */
int			parse_argv(int argc, char **argv);

/// ============================================================================
// UTILS.C
// =============================================================================
/**
 * @brief converts a string to int.
 * 
 * @param s to_convert
 * @return int 
 */
int			ft_atoi(char *s);

/**
 * @brief return time in milliseconds.
 * 
 * @return long 
 */
long		get_time(void);

/**
 * @brief write philo status on stdout.
 * 
 * @param philo 
 * @param status enum indicating philo status
 * @param debug if true, redirects to write_status_debug
 */
void		write_status(t_philo *philo, t_status status, bool debug);

/**
 * @brief wait for current time to be equal to start.
 * 
 * @param start 
 */
void		wait_threads(time_t start);

/// ============================================================================
// ROUTINE.C
// =============================================================================
/**
 * @brief philosopher routine. each philo while eat sleep and think.
 * 
 * @param data philosopher
 * @return void* 
 */
void		*routine(void *data);

/// ============================================================================
// INIT.C
// =============================================================================
/**
 * @brief initialize the program's values, philosophers and mutexes.
 * 
 * @param argc 
 * @param argv 
 * @return t_prog* upon failure, NULL is returned
 */
t_prog		*init_program(int argc, char **argv);

/// ============================================================================
// MONITOR.C
// =============================================================================
/**
 * @brief monitor routine that will continuously check if a philosopher
 * died or if all of the philosophers are full. if its the case, it will raise
 * the stop flag.
 * 
 * @param data program
 * @return void* 
 */
void		*monitor(void *data);

/// ============================================================================
// EXIT.C
// =============================================================================
/**
 * @brief free forks array, philosopher array, destroy mutexes and 
 * join / detach threads. 
 * 
 * @param p 
 */
void		exit_program(t_prog	*p);

/**
 * @brief display msg on stdout and return EXIT_FAILURE.
 * 
 * @param msg 
 * @return int 
 */
int			error_message(char *msg);

/**
 * @brief check if stop flag has been turned to true.
 * 
 * @param p 
 * @return true if stop = true
 * @return false 
 */
bool		is_finished(t_prog *p);

/**
 * @brief pause a philo for sleep_time while checking on if stop flag
 * has been set to true.
 * 
 * @param p 
 * @param sleep_time 
 */
void		sleep_philo(t_prog *p, time_t sleep_time);

//DEBUG.C
/**
 * @brief write status of the philo when DEBUG is set to true. Adds color
 * formatting and forks id.
 * 
 * @param philo 
 * @param status enum indicating philo status
 * @param msg to print
 */
void		write_status_debug(t_philo *philo, t_status status, char *msg);

bool	take_fork(t_philo *philo);
void	drop_fork(t_philo *philo);

#endif