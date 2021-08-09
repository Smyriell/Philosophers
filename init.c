/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:42:21 by smyriell          #+#    #+#             */
/*   Updated: 2021/08/09 18:51:18 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	common_struct_init(char **argv, t_data *input_data)
{
	input_data->philo_nbr = ft_atoi(argv[1]);
	input_data->time_to_die = ft_atoi_long(argv[2]);
	input_data->eating_time = ft_atoi_long(argv[3]);
	input_data->sleeping_time = ft_atoi_long(argv[4]);
	if (argv[5])
		input_data->times_to_eat_optional = ft_atoi(argv[5]);
	else
		input_data->times_to_eat_optional = -1;
	input_data->start_time = get_time();
}

int	each_phil_arr_init(t_data *input_data)
{
	int	i;

	input_data->one_phil = (t_phil *)malloc(input_data->philo_nbr * \
															sizeof(t_phil));
	if (!input_data->one_phil)
		return (ft_str_error("Error! Memmory allocation\n"));
	i = -1;
	while (++i < input_data->philo_nbr)
	{
		input_data->one_phil[i].id = i;
		input_data->one_phil[i].numb_of_meal = 0;
		input_data->one_phil[i].l_fork = i;
		input_data->one_phil[i].r_fork = (i + 1) % input_data->philo_nbr;
		input_data->one_phil[i].dead = 0;
		input_data->one_phil[i].input_data = input_data;
	}
	return (0);
}

int	mutex_init(t_data *input_data)
{
	int	i;

	input_data->forks = (pthread_mutex_t *)malloc(input_data->philo_nbr * \
													sizeof(pthread_mutex_t));
	if (!input_data->forks)
		return (ft_str_error("Error! Memmory allocation\n"));
	i = -1;
	while (++i < input_data->philo_nbr)
	{
		if (pthread_mutex_init(&input_data->forks[i], NULL))
			return (ft_str_error("Error! Mutex for philo was not inited\n"));
	}
	if (pthread_mutex_init(&input_data->print_lock, NULL))
		return (ft_str_error("Error! Mutex for messages was not inited\n"));
	return (0);
}
