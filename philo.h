/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:22:39 by smyriell          #+#    #+#             */
/*   Updated: 2021/07/28 20:26:25 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct  s_data
{
	int				philo_nbr;
	long int		dying_time;
	long int		eating_time;
	long int		sleeping_time;
	long int		start_time;
	long int		last_meal;
	int				already_ate;
	int				meal_times;
}               t_data;

int ft_strlen(char *str);
int ft_str_error(char *str);
int		ft_is_digit(char **mas);
unsigned int	ft_atoi(const char *s);

#endif
