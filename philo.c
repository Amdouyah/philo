/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:30:00 by amdouyah          #+#    #+#             */
/*   Updated: 2023/06/08 23:54:38 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int  timesamp()
{
    struct timeval time;
    gettimeofday(&time,NULL);
    return((time.tv_sec*1000) + (time.tv_usec/1000));
}

void	*routine(void *das)
{
	t_p		*ar;

	ar = (t_p *)das;
	if (ar->id % 2 != 0)
		usleep(200);
	while(1)
	{
		pthread_mutex_lock(&ar->arg->print_mutex);
		printf("%ld %d is thinking\n", timesamp() - ar->arg->time_start,ar->id);
		pthread_mutex_unlock(&ar->arg->print_mutex);
		pthread_mutex_lock(&ar->arg->forks[ar->right_fork]);
		pthread_mutex_lock(&ar->arg->print_mutex);
		printf("%ld %d has taking a fork\n", timesamp() - ar->arg->time_start, ar->id);
		pthread_mutex_unlock(&ar->arg->print_mutex);
		pthread_mutex_lock(&ar->arg->forks[ar->left_fork]);
		// printf("[%d]\n", ar->right_fork);
		// printf("{%d}\n", ar->left_fork);
		pthread_mutex_lock(&ar->arg->print_mutex);
		printf("%ld %d has taking a fork\n", timesamp()- ar->arg->time_start, ar->id);
		pthread_mutex_unlock(&ar->arg->print_mutex);
		pthread_mutex_lock(&ar->arg->print_mutex);
		ar->eat_time = timesamp() - ar->arg->time_start;
		printf("%ld %d is eating\n", timesamp()- ar->arg->time_start, ar->id);
		pthread_mutex_unlock(&ar->arg->print_mutex);
		usleep__(ar->arg->time_to_eat);
		pthread_mutex_unlock(&ar->arg->forks[ar->right_fork]);
		pthread_mutex_unlock(&ar->arg->forks[ar->left_fork]);
		pthread_mutex_lock(&ar->arg->print_mutex);
		printf("%ld %d is sleeping\n", timesamp()- ar->arg->time_start, ar->id);
		pthread_mutex_unlock(&ar->arg->print_mutex);
		usleep__(ar->arg->time_to_sleep);
		// printf("LOOOL\n");
	}
	return (NULL);
}
void	usleep__(long int s)
{
	long int	start;
	start = timesamp();
	while (timesamp() - start < s)
	{
		usleep(200);
	}
}
void init_forks(t_all *st)
{
	int i;

	i = 0;
	while (i < st->n_philo)
	{
		pthread_mutex_init(&st->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&st->print_mutex, NULL);
	pthread_mutex_init(&st->data_race, NULL);
}
void	init_philo(t_all *st)
{
	int	i;
	t_p *ar;

    ar = malloc(sizeof(t_p) * st->n_philo);
	i = 0;
	while(i < st->n_philo)
	{
		ar[i].id = i + 1;
		ar[i].arg = st;
		ar[i].right_fork = ar[i].id;
		ar[i].left_fork = (ar[i].id % ar->arg->n_philo) + 1;
		ar[i].eat_time = timesamp();
		pthread_create(&ar[i].philospher, NULL, &routine, &ar[i]);
		usleep(10);
		i++;
	}
	i = 0;
	while (i < st->n_philo)
	{
		pthread_join(ar[i].philospher, NULL);
		i++;
	}
}
// void	join_philo(t_p *ar)
// {
// 	int	i;
	
// }

int main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		t_all	*st;
		// t_p		*ar;
		// ar = NULL;
		// int	i;

	    st = malloc(sizeof(t_all));
		st->n_philo = ft_atoi(av[1]);
		st->time_to_die = ft_atoi(av[2]);
		st->time_to_eat = ft_atoi(av[3]);
		st->time_to_sleep = ft_atoi(av[4]);
		st->forks = malloc(sizeof(pthread_mutex_t) * st->n_philo);
		init_forks(st);
		st->time_start = timesamp();
		init_philo(st);
		// join_philo(ar);
		write(1, "X", 1);
	}
	else 
		return (0);
}
