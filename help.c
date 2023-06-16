/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:31:49 by amdouyah          #+#    #+#             */
/*   Updated: 2023/06/16 10:22:24 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_print(char *str, t_p *ar)
{
	pthread_mutex_lock(&ar->arg->print_mutex);
	printf("%ld %d %s\n", timesamp() - ar->arg->time_start, ar->id, str);
	pthread_mutex_unlock(&ar->arg->print_mutex);
}

int	ft_atoi(const char *str)
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
