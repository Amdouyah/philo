/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:30:00 by amdouyah          #+#    #+#             */
/*   Updated: 2023/06/18 15:56:23 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int  timesamp()
{
    struct timeval time;
    gettimeofday(&time,NULL);
    return((time.tv_sec*1000) + (time.tv_usec/1000));
}

int	check_meals(t_p *ar)
{
	pthread_mutex_lock(&ar->arg->data_race);
	ar->meals--;
	if (ar->meals == 0)
	{
		// pthread_mutex_unlock(&ar->arg->data_race);
		ar->arg->philo_count--;
		if (ar->arg->philo_count == 0)
		{
			pthread_mutex_unlock(&ar->arg->data_race);	
			return (1);
		}
	}
	pthread_mutex_unlock(&ar->arg->data_race);
	return 0;
}

void	*routine(void *das)
{
	t_p		*ar;
	// int		flag;

	ar = (t_p *)das;
	ar->flag_l_f = 0;
	ar->flag_r_f = 0;
	if (ar->id % 2 == 0)
		usleep(200);
	while(!ar->arg->flag)
	{
		if (ar->arg->philo_count == 0)
			break ;
		// printf("{%ld}\n", timesamp() - ar->arg->last_meal);
		ft_print("is thinking", ar);
		// if (ar->flag_r_f == 0)
		// {
			pthread_mutex_lock(&ar->arg->forks[ar->right_fork]);
			// ar->flag_r_f = 1;
			ft_print("has taken a fork", ar);
		// }
		// if (ar->flag_r_f == 1 && ar->flag_l_f == 0)
		// {
			pthread_mutex_lock(&ar->arg->forks[ar->left_fork]);
			ft_print("has taken a fork", ar);
			// ar->flag_l_f = 1;

		// }
		// if (ar->flag_r_f == 1 && ar->flag_l_f == 1)
		// {
			// ar->eat_time = timesamp( ) - ar->arg->time_start;
			pthread_mutex_lock(&ar->arg->data_race);
			ar->last_meal = timesamp();
			pthread_mutex_unlock(&ar->arg->data_race);
			ft_print("is eating", ar);
			usleep__(ar->arg->time_to_eat);
			pthread_mutex_unlock(&ar->arg->forks[ar->right_fork]);
			pthread_mutex_unlock(&ar->arg->forks[ar->left_fork]);
			// ar->flag_l_f = 0;
			// ar->flag_r_f = 0;
			ft_print("is sleeping", ar);
			usleep__(ar->arg->time_to_sleep);
			if (check_meals(ar))
				break ;
			// printf("%ld\n",timesamp() - ar->last_meal);
		// }
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
		usleep(50);
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
// void tst(t_p *ar, int i)
// {
// 	printf("{time is %ld}\n", timesamp() - ar[i].arg->last_meal);
// 			sleep(10);
// }
void	init_philo(t_all *st, int ac)
{
	int	i;
	t_p *ar;

    ar = malloc(sizeof(t_p) * st->n_philo);
	i = 0;
	st->philo_count = st->n_philo;
	while(i < st->n_philo)
	{
		ar[i].id = i + 1;
		ar[i].arg = st;
		ar[i].right_fork = i;
		ar[i].left_fork = (i + 1) % ar->arg->n_philo;
		ar[i].last_meal = timesamp();
		ar[i].eat_time = timesamp();
		ar[i].meals = ar->arg->n_t_eat;
		pthread_create(&ar[i].philospher, NULL, &routine, &ar[i]);
		usleep(10);
		i++;
	}
	i = 0;
	while(1)
	{
		i = 0;
		while(i < st->n_philo)
		{
			pthread_mutex_lock(&(ar[i].arg->data_race));
			if (st->philo_count == 0 && ac == 6)
			{
				pthread_mutex_unlock(&(ar[i].arg->data_race));
					join_philo(ar, st);
					mutex_des(ar, st);
				return ;
			}
			pthread_mutex_unlock(&(ar[i].arg->data_race));
			pthread_mutex_lock(&(ar[i].arg->data_race));
			if (timesamp() - ar[i].last_meal >= ar->arg->time_to_die && ar->arg->flag == 0)
			{
				pthread_mutex_lock(&(ar[i].arg->print_mutex));
					printf("%ld %d %s\n", timesamp() - ar->arg->time_start, ar->id,"died");
				pthread_mutex_unlock(&(ar[i].arg->print_mutex));
					ar->arg->flag = 1;
					// pthread_mutex_unlock(&ar->arg->forks[ar->right_fork]);
					// pthread_mutex_unlock(&ar->arg->forks[ar->left_fork]);
					pthread_mutex_unlock(&(ar[i].arg->data_race));
					join_philo(ar, st);
					mutex_des(ar, st);
					return ;
				// // exit(1);
			}
			pthread_mutex_unlock(&(ar[i].arg->data_race));
			i++;
		}
	}
	join_philo(ar, st);
	mutex_des(ar, st);
}
void	join_philo(t_p *ar, t_all *st)
{
	int i;
	
	i = 0;
	while (i < st->n_philo)
	{
		pthread_join(ar[i].philospher, NULL);
		i++;
	}
	
}

int main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		t_all	*st;
		t_p		*ar;
		ar = NULL;
		// int	i;

	    st = malloc(sizeof(t_all));
		st->n_philo = ft_atoi(av[1]);
		st->time_to_die = ft_atoi(av[2]);
		st->time_to_eat = ft_atoi(av[3]);
		st->time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
		{
			st->n_t_eat = ft_atoi(av[5]);
			if (st->n_t_eat == 0)
				return 0;
		}
		st->forks = malloc(sizeof(pthread_mutex_t) * st->n_philo);
		init_forks(st);
		st->time_start = timesamp();
		st->flag = 0;
		init_philo(st, ac);
	}
	else 
		return (0);
}

void	mutex_des(t_p *ar, t_all *st)
{
	int	i;
	i = 0;
	while (i < ar->arg->n_philo)
	{
		pthread_mutex_destroy(ar[i].arg->forks);
		i++;
	}
	pthread_mutex_destroy(&ar->arg->print_mutex);
	free(ar->arg->forks);
	free(st);
	free(ar);
}
