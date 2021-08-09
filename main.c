/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 16:19:06 by smyriell          #+#    #+#             */
/*   Updated: 2021/08/09 18:52:17 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_data *input_data)
{
	int	i;

	i = -1;
	while (++i < input_data->philo_nbr)
		pthread_mutex_destroy(&input_data->forks[i]);
	pthread_mutex_destroy(&input_data->print_lock);
	free(input_data->monitor_thread);
	free(input_data->forks);
	free(input_data);
}

int	ft_data_validation(char **argv)
{
	int			i;
	long long	n;	

	i = 0;
	if (ft_is_digit(argv))
		return (ft_str_error("Invalid format of argument\n"));
	while (argv[++i])
	{
		if (i == 1 || i == 5)
			n = ft_atoi(argv[i]);
		else
			n = ft_atoi_long(argv[i]);
		if (i == 1 && n < 1)
			return (ft_str_error("Error! Invalid number of Philosophers\n"));
		if (n < 60 && (i == 2 || i == 3 || i == 4))
			return (ft_str_error("Error! Invalid time of the action\n"));
	}
	return (0);
}

int	run_philo(char **argv)
{
	t_data	*input_data;
	t_phil	*one_phil;
	int	i;

	input_data = (t_data *)malloc(sizeof(t_data));
	if (!input_data)
		return (ft_str_error("Error! Memmory allocation\n"));
	input_data->monitor_thread = (pthread_t *)malloc(sizeof(pthread_t));
	if (!input_data->monitor_thread)
		return (ft_str_error("Error! Memmory allocation\n"));
	common_struct_init(argv, input_data);
	if (mutex_init(input_data) || each_phil_arr_init(input_data))
		return (1);
	if (create_threads(input_data))
		return (1);
	ft_free(input_data);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (ft_str_error("Error! Wrong number of arguments\n"));
	if (ft_data_validation(argv))
		return (1);
	if (run_philo(argv))
		return (1);
	return (0);
}
