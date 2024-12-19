/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:21:14 by dsiroten          #+#    #+#             */
/*   Updated: 2024/12/19 15:54:50 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		pthread_join(table->philosophers[i]->thread, NULL);
		i++;
	}
	pthread_join(table->death_monitor, NULL);
}

int	simulation_status(t_philosopher *philosopher, int status)
{
	pthread_mutex_lock(&philosopher->table->death_mutex);
	if (status == 0)
		philosopher->table->end = 1;
	if (philosopher->table->end == 1)
	{
		pthread_mutex_unlock(&philosopher->table->death_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philosopher->table->death_mutex);
	return (1);
}

void	to_eat(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->left_fork);
	to_log(philosopher, "has taken a fork");
	if (philosopher->table->number_of_philosophers == 1)
	{
		ft_usleep(philosopher->table->time_to_die * 2 * 1000);
		return ;
	}
	pthread_mutex_lock(philosopher->right_fork);
	to_log(philosopher, "has taken a fork");
	pthread_mutex_lock(&philosopher->table->eating_mutex);
	philosopher->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philosopher->table->eating_mutex);
	philosopher->times_eaten++;
	to_log(philosopher, "is eating");
	ft_usleep(philosopher->table->time_to_eat);
	pthread_mutex_unlock(philosopher->right_fork);
	pthread_mutex_unlock(philosopher->left_fork);
}

void	to_log(t_philosopher *philosopher, char *log)
{
	long int	stamp;

	pthread_mutex_lock(&philosopher->table->start_mutex);
	stamp = get_current_time() - philosopher->table->start_time;
	pthread_mutex_unlock(&philosopher->table->start_mutex);
	pthread_mutex_lock(&philosopher->table->log_mutex);
	if (simulation_status(philosopher, 1) || my_strcmp(log, "died") == 0)
		printf("%ld %d %s\n", stamp, philosopher->id, log);
	pthread_mutex_unlock(&philosopher->table->log_mutex);
}

void	to_finish_eating(t_philosopher *philosopher)
{
	if (philosopher->times_eaten
		== philosopher->table->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(&philosopher->table->monitor_mutex);
		philosopher->table->number_of_philosophers_done_eating++;
		if (philosopher->table->number_of_philosophers_done_eating
			== philosopher->table->number_of_philosophers)
			simulation_status(philosopher, 0);
		pthread_mutex_unlock(&philosopher->table->monitor_mutex);
	}
}

void	*life_monitor(void *arg)
{
	t_philosopher	*philosopher;
	int				start;

	philosopher = (t_philosopher *)arg;
	start = 0;
	while (!start)
	{
		pthread_mutex_lock(&philosopher->table->start_mutex);
		start = philosopher->table->start;
		pthread_mutex_unlock(&philosopher->table->start_mutex);
		continue ;
	}
	if (philosopher->id % 2 == 0)
		ft_usleep(philosopher->table->time_to_eat / 10);
	while (simulation_status(philosopher, 1) != 0)
	{
		to_eat(philosopher);
		if (philosopher->times_eaten == philosopher->table->number_of_times_each_philosopher_must_eat)
		{
			pthread_mutex_lock(&philosopher->table->monitor_mutex);
			philosopher->table->number_of_philosophers_done_eating++;
			if (philosopher->table->number_of_philosophers_done_eating
				== philosopher->table->number_of_philosophers)
			{
				pthread_mutex_unlock(&philosopher->table->monitor_mutex);
				simulation_status(philosopher, 0);
				return (NULL);
			}
			pthread_mutex_unlock(&philosopher->table->monitor_mutex);
			return (NULL);
		}
		to_log(philosopher, "is sleeping");
		ft_usleep(philosopher->table->time_to_sleep);
		to_log(philosopher, "is thinking");
	}
	return (0);
}

void *death_monitor(void *arg)
{
	t_table *table = (t_table *)arg;
	long current_time;
	int i;
	int	start;

	start = 0;
	while (!start)
	{
		pthread_mutex_lock(&table->start_mutex);
		start = table->start;
		pthread_mutex_unlock(&table->start_mutex);
		continue ;
	}
	while (simulation_status(table->philosophers[0], 1) != 0)
	{
		i = 0;
		ft_usleep(1000);
		while (i < table->number_of_philosophers)
		{
			if (simulation_status(table->philosophers[i], 1) == 0)
				return (NULL);
			current_time = get_current_time();
			pthread_mutex_lock(&table->eating_mutex);
			if (current_time - table->philosophers[i]->last_meal_time > table->time_to_die)
			{
				pthread_mutex_unlock(&table->eating_mutex);
				simulation_status(table->philosophers[i], 0);
				to_log(table->philosophers[i], "died");
				return (NULL);
			}
			pthread_mutex_unlock(&table->eating_mutex);
			i++;
		}
	}
	return (NULL);
}

void	stop_simulation(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		pthread_mutex_destroy(table->forks[i]);
		i++;
	}
	i = 0;
	while (i < table->number_of_philosophers)
	{
		free(table->philosophers[i]);
		i++;
	}
	pthread_mutex_destroy(&table->eating_mutex);
	pthread_mutex_destroy(&table->log_mutex);
	pthread_mutex_destroy(&table->monitor_mutex);
	pthread_mutex_destroy(&table->death_mutex);
	free(table->forks);
	free(table);
}

int	start_simulation(t_table *table)
{
	int i;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		if (pthread_create(&table->philosophers[i]->thread, NULL, life_monitor, table->philosophers[i]) != 0)
			return (0);
		i++;
	}
	i = 0;
	if (pthread_create(&table->death_monitor, NULL, death_monitor, table) != 0)
		return (0);
	pthread_mutex_lock(&table->start_mutex);
	table->start_time = get_current_time();
	while (i < table->number_of_philosophers)
	{
		pthread_mutex_lock(&table->eating_mutex);
		table->philosophers[i]->last_meal_time = table->start_time;
		pthread_mutex_unlock(&table->eating_mutex);
		i++;
	}
	table->start = 1;
	pthread_mutex_unlock(&table->start_mutex);
	return (1);
}
