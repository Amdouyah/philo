/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:30:00 by amdouyah          #+#    #+#             */
/*   Updated: 2023/06/18 22:12:29 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine2(t_p *ar)
{
	pthread_mutex_unlock(&ar->arg->data_race);
	ft_print("is thinking", ar);
	pthread_mutex_lock(&ar->arg->forks[ar->right_fork]);
	ft_print("has taken a fork", ar);
	pthread_mutex_lock(&ar->arg->forks[ar->left_fork]);
	ft_print("has taken a fork", ar);
	pthread_mutex_lock(&ar->arg->data_race);
	ar->last_meal = time_s();
	pthread_mutex_unlock(&ar->arg->data_race);
	ft_print("is eating", ar);
	usleep__(ar->arg->time_to_eat);
	pthread_mutex_unlock(&ar->arg->forks[ar->right_fork]);
	pthread_mutex_unlock(&ar->arg->forks[ar->left_fork]);
	ft_print("is sleeping", ar);
	usleep__(ar->arg->time_to_sleep);
}

void	*routine(void *das)
{
	t_p	*ar;

	ar = (t_p *)das;
	if (ar->id % 2 == 0)
		usleep(200);
	if (ar->arg->n_philo == 1)
	{
		ft_print("is thinking", ar);
		ft_print("has taken a fork", ar);
		return (NULL);
	}
	while (!ar->arg->flag)
	{
		pthread_mutex_lock(&ar->arg->data_race);
		if (ar->arg->philo_count == 0)
		{
			pthread_mutex_unlock(&ar->arg->data_race);
			break ;
		}
		routine2(ar);
		if (check_meals(ar))
			break ;
	}
	return (NULL);
}

t_p	*init_philo2(t_all *st)
{
	int	i;
	t_p	*ar;

	ar = malloc(sizeof(t_p) * st->n_philo);
	st->philo_count = st->n_philo;
	i = 0;
	while (i < st->n_philo)
	{
		ar[i].id = i + 1;
		ar[i].arg = st;
		ar[i].right_fork = i;
		ar[i].left_fork = (i + 1) % ar->arg->n_philo;
		ar[i].last_meal = time_s();
		ar[i].meals = ar->arg->n_t_eat;
		pthread_create(&ar[i].philospher, NULL, routine, &ar[i]);
		usleep(10);
		i++;
	}
	return (ar);
}

void	init_philo(t_all *st, int ac)
{
	int	i;
	t_p	*ar;

	ar = init_philo2(st);
	while (1)
	{
		i = -1;
		while (++i < st->n_philo)
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
			if (dead(st, ar, i))
				return ;
			pthread_mutex_unlock(&(ar[i].arg->data_race));
		}
	}
	join_philo(ar, st);
	mutex_des(ar, st);
}

int	main(int ac, char **av)
{
	t_all	*st;
	t_p		*ar;

	if (ac == 5 || ac == 6)
	{
		ar = NULL;
		st = malloc(sizeof(t_all));
		st->n_philo = ft_atoi(av[1]);
		st->time_to_die = ft_atoi(av[2]);
		st->time_to_eat = ft_atoi(av[3]);
		st->time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
		{
			st->n_t_eat = ft_atoi(av[5]);
			if (st->n_t_eat == 0)
				return (0);
		}
		st->forks = malloc(sizeof(pthread_mutex_t) * st->n_philo);
		init_forks(st);
		st->time_start = time_s();
		st->flag = 0;
		init_philo(st, ac);
	}
	else
		return (0);
}
