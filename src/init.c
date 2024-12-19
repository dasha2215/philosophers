/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:21:05 by dsiroten          #+#    #+#             */
/*   Updated: 2024/12/19 15:59:00 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	assign_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		if (i - 1 >= 0)
			table->philosophers[i]->left_fork = table->forks[i - 1];
		else
			table->philosophers[i]->left_fork
				= table->forks[table->number_of_philosophers - 1];
		table->philosophers[i]->right_fork = table->forks[i];
		i++;
	}
}

int	init_forks(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t)
			* table->number_of_philosophers);
	if (!table->forks)
		return (0);
	while (i < table->number_of_philosophers)
	{
		table->forks[i] = malloc(sizeof(pthread_mutex_t));
		if (!table->forks[i])
			return (0);
		if (pthread_mutex_init(table->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	init_philosophers(t_table *table)
{
	t_philosopher	*philosopher;
	int				i;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		table->philosophers[i] = malloc(sizeof(t_philosopher));
		if (!table->philosophers[i])
			return (0);
		philosopher = table->philosophers[i];
		philosopher->id = i + 1;
		philosopher->times_eaten = 0;
		philosopher->table = table;
		i++;
	}
	return (1);
}

int	init_table(t_table *table, int argc, char **argv)
{
	table->number_of_philosophers = my_atoi(argv[1]);
	table->time_to_die = my_atoi(argv[2]);
	table->time_to_eat = my_atoi(argv[3]) * 1000;
	table->time_to_sleep = my_atoi(argv[4]) * 1000;
	table->end = 0;
	table->start = 0;
	if (argc == 6)
		table->number_of_times_each_philosopher_must_eat = my_atoi(argv[5]);
	else
		table->number_of_times_each_philosopher_must_eat = -1;
	table->number_of_philosophers_done_eating = 0;
	table->philosophers = malloc(sizeof(t_philosopher)
			* table->number_of_philosophers);
	if (!table->philosophers)
		return (0);
	return (1);
}

int	create_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->log_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&table->eating_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&table->monitor_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&table->death_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&table->start_mutex, NULL) != 0)
		return (0);
	return (1);
}


int	init_simulation(t_table *table, int argc, char **argv)
{
	if (!init_table(table, argc, argv))
		return (0);
	if (!init_philosophers(table))
		return (0);
	if (!create_mutexes(table))
		return (0);
	if (!init_forks(table))
		return (0);
	assign_forks(table);
	return (1);
}
