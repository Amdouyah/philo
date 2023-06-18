/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:50:05 by amdouyah          #+#    #+#             */
/*   Updated: 2023/06/18 18:41:30 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	time_s(void)
{
	struct timeval	time;

	gettimeofday (&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	check_meals(t_p *ar)
{
	pthread_mutex_lock(&ar->arg->data_race);
	ar->meals--;
	if (ar->meals == 0)
	{
		ar->arg->philo_count--;
		if (ar->arg->philo_count == 0)
		{
			pthread_mutex_unlock(&ar->arg->data_race);
			return (1);
		}
	}
	pthread_mutex_unlock(&ar->arg->data_race);
	return (0);
}

void	join_philo(t_p *ar, t_all *st)
{
	int	i;

	i = 0;
	while (i < st->n_philo)
	{
		pthread_join(ar[i].philospher, NULL);
		i++;
	}
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
