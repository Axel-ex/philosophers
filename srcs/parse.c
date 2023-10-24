/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:45:45 by achabrer          #+#    #+#             */
/*   Updated: 2023/10/24 13:32:37 by achabrer         ###   ########.fr       */
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
	{
		printf("Enter a valid number of arguments.\n");
		return (-1);
	}
	if (!is_valid(argc, argv))
	{
		printf("Enter positive numeric arguments.\n");
		return (-1);
	}
	if (!is_non_zero(argc, argv))
	{
		printf("Enter non-zero arguments.\n");
		return (-1);
	}
	return (0);
}
