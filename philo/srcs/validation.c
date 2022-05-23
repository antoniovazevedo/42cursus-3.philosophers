/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 18:26:13 by aazevedo          #+#    #+#             */
/*   Updated: 2022/05/23 19:54:14 by aazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

static int	ft_atoi(const char *str)
{
	int	nbr;

	nbr = 0;
	while (ft_isdigit(*str))
		nbr = (nbr * 10) + (*str++ - '0');
	return (nbr);
}

t_main	*fill_input_from_args(int argc, char **args)
{
	t_main	*main;

	main = (t_main *) malloc(sizeof(t_main));
	main->philo_count = ft_atoi(args[1]);
	main->time_to_die = ft_atoi(args[2]);
	main->time_to_eat = ft_atoi(args[3]);
	main->time_to_sleep = ft_atoi(args[4]);
	if (argc == 6)
		main->number_of_times_each_philosopher_must_eat = ft_atoi(args[5]);
	return (main);
}
