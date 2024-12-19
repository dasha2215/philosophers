/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:20:46 by dsiroten          #+#    #+#             */
/*   Updated: 2024/12/19 15:58:33 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_table
{
	long					start_time;
	int						number_of_philosophers;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						number_of_times_each_philosopher_must_eat;
	int						number_of_philosophers_done_eating;
	int						end;
	int						start;
	pthread_t				death_monitor;
	pthread_mutex_t			**forks;
	struct s_philosopher	**philosophers;
	pthread_mutex_t			log_mutex;
	pthread_mutex_t			eating_mutex;
	pthread_mutex_t			monitor_mutex;
	pthread_mutex_t			death_mutex;
	pthread_mutex_t			start_mutex;
}	t_table;

typedef struct s_philosopher
{
	int				id;
	int				times_eaten;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_table			*table;
}	t_philosopher;

int		are_args_valid(int argc, char **argv);

int		init_simulation(t_table *table, int argc, char **argv);
int		init_table(t_table *table, int argc, char **argv);
int		init_philosophers(t_table *table);
int		init_forks(t_table *table);
void	assign_forks(t_table *table);

int		start_simulation(t_table *table);
void	*life_monitor(void *arg);
void	*death_monitor(void *arg);
void	to_log(t_philosopher *philosopher, char *log);
void	join_threads(t_table *table);
void	stop_simulation(t_table *table);

int		my_atoi(const char *str);
int		my_strcmp(const char *s1, const char *s2);
long	get_current_time(void);
int		is_prioritized(t_philosopher *philosopher);
int		end_condition_reached(t_table *table, t_philosopher *philosopher,
			long current_time);
int		terminate_philosopher(t_philosopher *philosopher);
void	ft_usleep(long int time_in_microseconds);

#endif