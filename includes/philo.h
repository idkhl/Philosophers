/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:37:33 by idakhlao          #+#    #+#             */
/*   Updated: 2024/12/03 17:55:57 by idakhlao         ###   ########.fr       */
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
	int				nb_philo;
	int				die;
	int				eat;
	int				sleep;
	int				nb_eat;
	int				is_alive;
	long int		start;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	mutex_alive;
	pthread_mutex_t	*forks;
}	t_data;

typedef struct s_philo
{
	int				index;
	int				ate;
	long int		last_ate;
	pthread_mutex_t	mutex;
	t_data			*data;
}	t_philo;

/* UTIILS */

int			ft_atoi(const char *str);
long int	get_time(void);
int			ft_strcmp(char *s1, char *s2);

#endif
