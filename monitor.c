/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 18:15:17 by smyriell          #+#    #+#             */
/*   Updated: 2021/08/09 19:07:57 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	each_phil_fullfed(t_data *input_data)
{
	int	i;
	int	full_phil;

	i = -1;
	full_phil = 0;
	while (++i < input_data->philo_nbr)
	{
		if (input_data->one_phil[i].numb_of_meal == \
									input_data->times_to_eat_optional)
			full_phil++;
	}
	if (full_phil == input_data->philo_nbr)
		return (1);
	else
		return (0);
}

int	check_starved_phil(t_data *input_data)
{
	int	i;

	i = -1;
	while (++i < input_data->philo_nbr)
	{
		if (get_time() > input_data->one_phil[i].death_time)
		{
			pthread_mutex_lock(&input_data->print_lock);
			action_data_output(&input_data->one_phil[i], \
										"\e[91mstarved to death\e[39m\n");
			input_data->one_phil[i].dead = 1;
			return (1);
		}
	}
	return (0);
}

void	*ft_monitor(void *input_data)
{
	t_data	*data_input;

	data_input = (t_data *)input_data;
	while (1)
	{
		if (check_starved_phil(data_input))
			break ;
		if (data_input->times_to_eat_optional != -1 && \
												each_phil_fullfed(data_input))
		{
			pthread_mutex_lock(&data_input->print_lock);
			printf("Times to eat for each philo = %d, everybody is full\n", \
											data_input->times_to_eat_optional);
			break ;
		}
	}
	return (NULL);
}
