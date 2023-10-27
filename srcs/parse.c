/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:45:45 by achabrer          #+#    #+#             */
/*   Updated: 2023/10/27 18:48:52 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	is_valid(int argc, char **argv)
{
	int	i;

	while (--argc > 1)
	{
		i = 0;
		while (argv[argc][i])
		{
			if (argv[argc][i] < '0' || argv[argc][i] > '9')
				return (false);
			i++;
		}
	}
	return (true);
}

static bool	is_non_zero(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
			return (false);
		i++;
	}
	return (true);
}

int	parse_argv(int argc, char **argv)
{
	if (argc < 5)
		return (error_message("Enter valid number of arguments\n"));
	if (!is_valid(argc, argv))
		return (error_message("Enter positive numeric arguments.\n"));
	if (!is_non_zero(argc, argv))
		return (error_message("Enter non-zero arguments.\n"));
	return (0);
}
