/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:37:33 by idakhlao          #+#    #+#             */
/*   Updated: 2024/11/18 17:15:15 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int	nb_philo;
	int	die;
	int	eat;
	int	sleep;
	int	nb_eat;
}	t_data;

typedef struct s_thread
{
	t_data	*philo;
	int		index;
}	t_thread;

int	ft_atoi(const char *str);

#endif