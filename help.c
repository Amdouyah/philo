/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:31:49 by amdouyah          #+#    #+#             */
/*   Updated: 2023/06/18 23:18:31 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	usleep__(long int s)
{
	long int	start;

	start = time_s();
	while (time_s() - start < s)
		usleep(50);
}

void	ft_print(char *str, t_p *ar)
{
	pthread_mutex_lock(&(ar->arg->data_race));
	if (ar->arg->flag == 0)
	{
		pthread_mutex_unlock(&(ar->arg->data_race));
		pthread_mutex_lock(&ar->arg->print_mutex);
		printf("%ld %d %s\n", time_s() - ar->arg->time_start, ar->id, str);
		pthread_mutex_unlock(&ar->arg->print_mutex);
	}
	else
		pthread_mutex_unlock(&(ar->arg->data_race));
}

void	init_forks(t_all *st)
{
	int	i;

	i = 0;
	while (i < st->n_philo)
	{
		pthread_mutex_init(&st->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&st->print_mutex, NULL);
	pthread_mutex_init(&st->data_race, NULL);
}

int	dead(t_all *st, t_p *ar, int i)
{
	pthread_mutex_lock(&(ar[i].arg->data_race));
	if (time_s() - ar[i].last_meal >= ar->arg->time_to_die
		&& ar->arg->flag == 0)
	{
		pthread_mutex_lock(&(ar[i].arg->print_mutex));
		printf("%ld %d %s\n", time_s() - ar->arg->time_start,
			ar->id, "died");
		pthread_mutex_unlock(&(ar[i].arg->print_mutex));
		ar->arg->flag = 1;
		pthread_mutex_unlock(&(ar[i].arg->data_race));
		join_philo(ar, st);
		mutex_des(ar, st);
		return (1);
	}
	return (0);
}

long	ft_atoi(const char *str)
{
	int	r;
	int	i;
	int	sign;

	r = 0;
	sign = 1;
	i = 0;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = (r * 10) + (str[i] - 48);
		i++;
	}
	return (r * sign);
}
