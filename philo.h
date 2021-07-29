/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:22:39 by smyriell          #+#    #+#             */
/*   Updated: 2021/07/29 03:13:57 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <semaphore.h>

typedef struct	s_phil
{
	int			id;
	long int	begin;
	int			numb_of_meal;
	
}				t_phil;

typedef struct  	s_data
{
	int				philo_nbr;
	long int		time_to_die;
	long int		eating_time;
	long int		sleeping_time;
	long int		start_time;
	int				times_to_eat;
	t_phil			*each_phil;
	pthread_t		*phil_thread;
	pthread_mutex_t	*forks;
}               	t_data;


//*  utils  *//

int ft_strlen(char *str);
int ft_str_error(char *str);
int		ft_is_digit(char **mas);
long long	ft_atoi(const char *s);
long int	current_time(void);

#endif
