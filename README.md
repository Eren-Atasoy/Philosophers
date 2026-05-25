# 🍝 Philosophers

This project is part of the 42 core curriculum. It serves as an introduction to the basics of threading a process and teaches how to create threads and discover mutexes.

## 📝 Overview
This project is an implementation of the classic **Dining Philosophers problem**.
- One or more philosophers sit at a round table.
- There is a large bowl of spaghetti in the middle of the table.
- The philosophers alternatively **eat**, **think**, or **sleep**.
- While they are eating, they are not thinking nor sleeping; while thinking, they are not eating nor sleeping; and, of course, while sleeping, they are not eating nor thinking.
- There are also forks on the table. There are as many forks as philosophers.
- Because serving and eating spaghetti with only one fork is very inconvenient, a philosopher takes their right and their left forks to eat, one in each hand.
- When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again. The simulation stops when a philosopher dies of starvation.

## ⚙️ Compilation

To compile the project, navigate to the `philo` directory and run `make`:
```bash
cd philo
make
```

## 🚀 Usage

Execute the program with the following arguments:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments:
* `number_of_philosophers`: The number of philosophers and also the number of forks.
* `time_to_die` (in milliseconds): If a philosopher didn't start eating `time_to_die` milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
* `time_to_eat` (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
* `time_to_sleep` (in milliseconds): The time a philosopher will spend sleeping.
* `number_of_times_each_philosopher_must_eat` (optional): If all philosophers have eaten at least this many times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

### Examples

No philosopher should die:
```bash
./philo 5 800 200 200
```

No philosopher should die, and the simulation should stop after all of them have eaten at least 7 times:
```bash
./philo 5 800 200 200 7
```

A philosopher should die:
```bash
./philo 4 310 200 100
```

## 🛠️ Implementation Details
- **Threading:** Each philosopher is represented by a separate thread (`pthread_create`).
- **Mutexes:** Mutexes (`pthread_mutex_t`) are used to protect the forks and prevent data races (e.g., when a philosopher picks up or puts down a fork, or when checking the death conditions).
- **Monitoring:** A separate observer mechanism continuously checks if any philosopher has starved or if the meal requirement is fulfilled, ensuring prompt termination of the simulation.
- **Norminette:** The codebase is fully compliant with the 42 C coding standard (Norminette v3).
