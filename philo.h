/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:22:39 by smyriell          #+#    #+#             */
/*   Updated: 2021/08/05 21:45:14 by smyriell         ###   ########.fr       */
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

typedef struct s_data	t_data;

typedef struct		s_phil
{
	int				id;
	long long			begin;// mili
	long long			finished;//mili
	int				numb_of_meal;
	int				left_fork;
	int				right_fork;
	int				dead;
	t_data			*input_data;
}					t_phil;

typedef struct  	s_data
{
	int				philo_nbr;
	long long		time_to_die;//mili
	long long		eating_time;//mili
	long long		sleeping_time;//mili
	long long		start_time;//mili
	int				times_to_eat_optional;
	t_phil			*one_phil;
	pthread_t		*phil_thread;
	pthread_t		*monitor_thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t monitor_lock;
	pthread_mutex_t	print_lock;
}               	t_data;


//*  utils  *//

time_t		get_time(void);
int			ft_strlen(char *str);
int			ft_str_error(char *str);
int			ft_is_digit(char **arr);
int			ft_atoi(const char *s);
long long	ft_atoi_long(const char *s);

//*  phil_actions  *//

int    phil_eat(t_phil *one_phil);
void	action_data_output(t_phil *one_phil, char *message);
void	bury_phil(t_data *input_data);
int		check_dead_phil(t_data *input_data);
int		each_phil_fullfed(t_data *input_data);


//*  main  *//

void	*ft_monitor(void *input_data);
int		ft_data_valid(char **argv);
void	common_struct_init(char **argv, t_data *input_data);
int		each_phil_arr_init(t_data *input_data);
int		mutex_init(t_data *input_data);
void	*ft_launching(void *one_of_philo);
int		threads(t_data *input_data);
int		start_philo(char **argv);


// int ft_strlen(char *str);
// int ft_str_error(char *str);
// int		ft_is_digit(char **mas);
// long long	ft_atoi(const char *s);
// long int	get_time(void);

#endif
