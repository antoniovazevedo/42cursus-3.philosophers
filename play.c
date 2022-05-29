/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 01:02:45 by aazevedo          #+#    #+#             */
/*   Updated: 2022/05/23 21:54:47 by aazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

void	*thread_main(void *ptr)
{
	int			*str;
	struct timeval	*time;

	str = (int *) ptr;
	time = (struct timeval*) malloc(sizeof(struct timeval));
	gettimeofday(time, NULL);
	sleep(2);
	printf("%ld.%d\tHello from thread %d...\n",  time->tv_sec, time->tv_usec, *str);
	free(time);
	return (NULL);
}

int	main(void)
{
	pthread_t	*thread1;
	pthread_t	*thread2;
	pthread_t	*thread3;

	thread1 = (pthread_t *)malloc(sizeof(pthread_t));
	thread2 = (pthread_t *)malloc(sizeof(pthread_t));
	thread3 = (pthread_t *)malloc(sizeof(pthread_t));

	int *nb;

	nb = (int *)malloc(sizeof(int));

	*nb = 23;

	pthread_create(thread1, NULL, &thread_main, nb);
	// pthread_create(thread2, NULL, &thread_main, "2");
	// pthread_create(thread3, NULL, &thread_main, "3");
	// pthread_join(*thread1, NULL);
	// pthread_join(*thread2, NULL);
	// pthread_join(*thread3, NULL);
	// printf("ending!\n");
	// printf("\npid:\t%d\n", getpid());
	sleep(5);
	return (0);
}
