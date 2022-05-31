/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 18:21:11 by aazevedo          #+#    #+#             */
/*   Updated: 2022/05/31 22:04:49 by aazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_params {
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				min_meal_count;
	long long		start_time;
	int				dead_philo_count;
	int				active;
	pthread_mutex_t	mutex;
}	t_params;

typedef struct s_fork
{
	int				nb;
	int				is_taken;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo
{
	int				nb;
	int				meal_count;
	long long		last_meal_at;
	enum e_philo_state
	{
		thinking = 0,
		eating = 1,
		sleeping = 2
	} state;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_mutex_t	mutex;
}	t_philo;

typedef struct s_main {
	t_params	*params;
	t_philo		*philo;
}	t_main;

t_params	*fill_input_from_args(int argc, char **args);

/* forks.c */
void		free_forks(t_fork **list, int count);
t_fork		**create_forks(int count);
int			pick_up_forks(t_fork *fork1, t_fork *fork2);
void		drop_forks(t_fork *fork1, t_fork *fork2);

/* threads.c */
int			create_threads(t_params *params, t_fork **forks);

/* philos.c */
void		print_state_message(int nb, char *state, t_params *params);
pthread_t	*initialize_philo_thread(t_params *params, int nb, t_fork **forks);
void		update_philo_state(t_params *params, t_philo *philo,
				enum e_philo_state state);

/* actions.c */
int			philo_eat(t_params *params, t_philo *philo);
void		philo_sleep(t_params *params, t_philo *philo);
void		philo_think(t_params *params, t_philo *philo);

/* main.c */
long long	get_time_ms(long long start_time);

/* state.c */
int			philo_dead_count(t_params *params);

#endif