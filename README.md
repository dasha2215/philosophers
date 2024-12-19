# Philosophers Project

## Overview
The Philosophers project is a simulation of the classic **Dining Philosophers Problem**, implemented as part of the 42 Bangkok curriculum. It showcases proficiency in multithreading, concurrency control, and process synchronization using threads and mutexes. 

---

## Features
- Simulates a dining table with philosophers who alternate between thinking, eating, and sleeping.
- Ensures no data races and handles concurrency using threads and mutexes.
- Accurate and timely logging of philosopher state changes (e.g., eating, thinking, dying).
- Handles edge cases such as a single philosopher and ensures philosophers avoid unnecessary starvation.

---

## How It Works
- One or more philosophers sit at a round table.
- There is a large bowl of spaghetti in the middle of the table.
- There are also forks on the table. **There are as many forks as philosophers**.
- **A philosopher needs two forks to eat**. They take the one on their right and the one on their left, one in each hand.
• When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking. 

Each philosopher alternates between three states:
1. **Thinking**: Philosophers think until they can acquire two forks (mutexes or semaphores).
2. **Eating**: Philosophers hold two forks and eat for a specified duration.
3. **Sleeping**: After eating, philosophers sleep for a specified duration before returning to thinking.

The simulation terminates if:
- A philosopher dies (fails to eat within the given time).
- All philosophers have eaten a specified number of times (optional argument).

## Compilation and Execution

### Mandatory Part
```bash
cd philo
make
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

### Example
Run the simulation with 5 philosophers:
```bash
./philo 5 800 200 200
```

Arguments:
- `number_of_philosophers`: Number of philosophers and forks.
- `time_to_die`: Time (in milliseconds) before a philosopher dies without eating.
- `time_to_eat`: Time (in milliseconds) a philosopher spends eating.
- `time_to_sleep`: Time (in milliseconds) a philosopher spends sleeping.
- `number_of_times_each_philosopher_must_eat` (optional): Stops the simulation after each philosopher eats this many times.
**Note:** As a general rule, time to die should be at least double of time to eat for an even number of philosophers and at least triple for an uneven number to avoid starvation.

---

## Author
This project is part of the 42 Bangkok curriculum and showcases advanced C programming skills in concurrency and process management.

- **Concurrency Management**: Efficient handling of shared resources (forks) using mutexes.
- **Multithreading**: Synchronization of threads to prevent data races and ensure correct simulation behavior.
- **Problem Solving**: Handling edge cases and ensuring the program meets real-time constraints.

**Note:** Norminette is only partially done for this project
