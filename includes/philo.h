/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:37:33 by idakhlao          #+#    #+#             */
/*   Updated: 2024/11/19 18:59:05 by idakhlao         ###   ########.fr       */
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
	int			nb_philo;
	int			die;
	int			eat;
	int			sleep;
	int			nb_eat;
	long int	start;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	int				index;
	pthread_mutex_t	*mutex;
	int				ate;
	long int		last_ate;
}	t_philo;

/* UTIILS */

int			ft_atoi(const char *str);
long int	get_time(void);

#endif
