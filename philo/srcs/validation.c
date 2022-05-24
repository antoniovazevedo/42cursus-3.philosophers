/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 18:26:13 by aazevedo          #+#    #+#             */
/*   Updated: 2022/05/24 01:19:03 by aazevedo         ###   ########.fr       */
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

t_params	*fill_input_from_args(int argc, char **args)
{
	int			philo_count;
	t_params	*params;

	philo_count = ft_atoi(args[1]);
	if (philo_count < 1)
	{
		printf("Error\nNumber of philosophers must be greater than 0.\n");
		return (NULL);
	}
	params = (t_params *) malloc(sizeof(t_params));
	params->philo_count = philo_count;
	params->time_to_die = ft_atoi(args[2]);
	params->time_to_eat = ft_atoi(args[3]);
	params->time_to_sleep = ft_atoi(args[4]);
	if (argc == 6)
		params->min_meal_count = ft_atoi(args[5]);
	return (params);
}
