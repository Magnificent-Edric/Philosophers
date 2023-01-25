# Philosophers project
   The Dining Philosophers Problem is a classic example used in computer science to illustrate synchronization problems in the development of parallel algorithms and techniques for solving these problems.The problem was formulated in 1965 by Edsger Dijkstra as an examination exercise for students.
   An indefinite number of silent philosophers sit around a round table, each philosopher has a bowl of spaghetti in front of them. Forks lie on the table between each pair of nearest philosophers. if they don't eat during time to die, they die
   
Every philosopher can either eat or meditate and even sleep
- number_of_philosophers: The number of philosophers and also the number
  of forks.
- time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
  milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
  During that time, they will need to hold two forks.
- time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
- number_of_times_each_philosopher_must_eat (optional argument): If all
  philosophers have eaten at least number_of_times_each_philosopher_must_eat
  times, the simulation stops. If not specified, the simulation stops when a
  philosopher dies.
  
  Solve:
   Each philosopher is assigned a fork, let it be the left one, the task uses mutex and thread. We launch them in two groups with a certain pause of 5000 ms, inside the function below, the forks will be taken, taking into account the fact that the previous one released.
  ```
  void	philo_get_forks(t_philos *philo, unsigned int fork_num)
  {
	  pthread_mutex_lock(philo->forks[fork_num]);
	  write_msg("has taken fork", philo);
	  if (philo->forks[0] == philo->forks[1])
	  {
		  delay_philo(philo->time_to_die + 1);
		  pthread_mutex_unlock(philo->forks[fork_num]);
	  }
  }

  static void	*philosopher(void *arg)
  {
	  t_philos	*args;

	  args = (t_philos *)arg;
	  while (1)
	  {
		  pthread_mutex_lock(args->finish_mutex);
		  if (*args->finish)
		  {
			  pthread_mutex_unlock(args->finish_mutex);
			  return (NULL);
		  }
		  pthread_mutex_unlock(args->finish_mutex);
		  if (args->num_eat <= 0 && args->check_eat > 0)
			  return (NULL);
		  philo_get_forks(args, 0);
		  philo_get_forks(args, 1);
		  philo_eat_sleep_thinking(args);
	  }
  }

  /** @brief This function inisializing group philo and lock/unlock
    * */
  static int	create_philo_work(unsigned int first,
							unsigned int step, t_data *data)
  {
	  while (first < (unsigned int) data->philo_num)
	  {
		  data->philos[first].thread_id = first;
		  if (pthread_create(&data->philos[first].thread_id, NULL,
				  philosopher, &data->philos[first]))
		  {
			  pthread_mutex_lock(&data->finish_mutex);
			  data->finish = true;
			  pthread_mutex_unlock(&data->finish_mutex);
			  return (ERROR);
		  }
		  first += step;
	  }  
	  return (SUCCESS);
  }

  /** @brief This function create two groups, which create two active work
   * @param 0 Inisializing first group with step  2
   * */
  int	philo_start(t_data *data)
  {
	  if (data->philo_num == 2 && data->philos[0].time_to_eat < 10
		  && data->philos[0].time_to_die < 10
		  && data->philos[0].time_to_sleep < 10)
	  {
		  if (!create_philo_work(0, 2, data))
			  return (ERROR);
		  usleep(300);
		  if (!create_philo_work(1, 2, data))
			  return (ERROR);
		  return (SUCCESS);
	  }
	  if (!create_philo_work(0, 2, data))
		  return (ERROR);
	  usleep(5000);
	  if (!create_philo_work(1, 2, data))
		  return (ERROR);
	  return (SUCCESS);
  }
```
