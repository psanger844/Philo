#ifndef TEST_H
# define TEST_H

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct			s_philo
{
	long				time;
	int					left_fork;
	int					right_fork;
	int					id;
	pthread_mutex_t		*mutex;
}						t_philo;


#endif
