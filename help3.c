/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:24:33 by amdouyah          #+#    #+#             */
/*   Updated: 2023/06/19 17:31:20 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_max(char *av)
{
	long	nbr;

	nbr = ft_atoi(av);
	if (nbr > 2147483647 || nbr <= 0)
		return (1);
	return (0);
}

int	init_argument(char **av, t_all *st)
{
	int	i;

	st->n_philo = ft_atoi(av[1]);
	st->time_to_die = ft_atoi(av[2]);
	st->time_to_eat = ft_atoi(av[3]);
	st->time_to_sleep = ft_atoi(av[4]);
	i = 1;
	while (i <= 4)
	{
		if (check_max(av[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}
