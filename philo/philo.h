/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:29:03 by amdouyah          #+#    #+#             */
/*   Updated: 2023/06/19 17:32:17 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_all{
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			n_philo;
	long			n_t_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	data_race;
	long int		time_start;
	int				flag;
	int				philo_count;
}t_all;

typedef struct s_p{
	long int	last_meal;
	t_all		*arg;
	pthread_t	philospher;
	int			meals;
	int			id;
	int			think;
	int			right_fork;
	int			left_fork;
	int			flag_r_f;
	int			flag_l_f;
}t_p
;

long		ft_atoi(const char *str);
void		usleep__(long int s, t_p *ar);
long int	time_s(void);
void		ft_print(char *str, t_p *ar);
void		mutex_des(t_p *ar, t_all *st);
void		join_philo(t_p *ar, t_all *st);
int			check_meals(t_p *ar);
void		init_forks(t_all *st);
int			dead(t_all *st, t_p *ar, int i);
int			check_d(char **str);
int			check_max(char *av);
int			init_argument(char **av, t_all *st);

#endif