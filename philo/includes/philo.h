/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 18:21:11 by aazevedo          #+#    #+#             */
/*   Updated: 2022/05/16 20:22:48 by aazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <stdlib.h>

typedef struct s_main {
	int	philo_count;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
}	t_main;

typedef struct s_philo {
	int	nb;
	enum e_philo_state{thinking = 0, eating = 1, sleeping = 2} state;
}	t_philo;

t_main	*fill_input_from_args(int argc, char **args);

#endif