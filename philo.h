/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:29:03 by amdouyah          #+#    #+#             */
/*   Updated: 2023/06/18 15:32:31 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct	s_all{
	
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_philo;
	int				n_t_eat;
	pthread_mutex_t *forks;
	pthread_mutex_t print_mutex;
	pthread_mutex_t data_race;
	long int		time_start;
	int				flag;
	int philo_count;
	// pthread_t		check_d;
	
}t_all;

typedef struct s_p{
	
	long int		last_meal;
	t_all *arg;
	pthread_t	philospher;
	int	meals;
	int id;
	int	think;
	int eat_time;
	int	right_fork;
	int	left_fork;
	int	flag_r_f;
	int	flag_l_f;
}t_p
;

int			ft_atoi(const char *str);
void		usleep__(long int s);
long int	timesamp();
void 		ft_print(char *str, t_p *ar);
void	mutex_des(t_p *ar, t_all *st);
void	join_philo(t_p *ar, t_all *st);
#endif