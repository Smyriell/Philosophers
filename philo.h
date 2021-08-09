/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:22:39 by smyriell          #+#    #+#             */
/*   Updated: 2021/08/09 23:15:01 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct s_data	t_data;

typedef struct s_phil
{
	int				id;
	long long		begin;
	long long		death_time;
	int				numb_of_meal;
	int				l_fork;
	int				r_fork;
	int				dead;
	t_data			*input_data;
}				t_phil;

typedef struct s_data
{
	int				philo_nbr;
	long long		time_to_die;
	long long		eating_time;
	long long		sleeping_time;
	long long		start_time;
	int				times_to_eat_optional;
	t_phil			*one_phil;
	pthread_t		*phil_thread;
	pthread_t		monitor_thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
}				t_data;

//*   main  *//

void		ft_free(t_data *input_data);
int			ft_data_validation(char **argv);
int			run_philo(char **argv);
int			main(int argc, char **argv);

//*  init  *//

void		common_struct_init(char **argv, t_data *input_data);
int			each_phil_arr_init(t_data *input_data);
int			mutex_init(t_data *input_data);

//*  create_threads  *//

void		phil_eat(t_phil *one_phil);
int			ft_check_phil_condition(t_phil *one_phil);
void		*ft_launching(void *one_of_philo);
int			create_threads(t_data *input_data);

//*   monitor  *//

int			each_phil_fullfed(t_data *input_data);
int			check_starved_phil(t_data *input_data);
void		*ft_monitor(void *input_data);

//*   utils  *//

time_t		get_time(void);
void		ft_usleep(long long interval);
int			ft_str_error(char *str);
void		print_message(t_phil *one_phil, char *str);
void		action_data_output(t_phil *one_phil, char *message);

//*   libft   *//

int			ft_strlen(char *str);
int			ft_is_digit(char **arr);
int			ft_atoi(const char *s);
long long	ft_atoi_long(const char *s);

#endif
