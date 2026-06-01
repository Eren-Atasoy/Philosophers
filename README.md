*This project has been created as part of the 42 curriculum by eratasoy.*

# Philosophers

## Description
This project is an implementation of the classic Dining Philosophers problem. Its main goal is to introduce the basics of threading a process. By completing this project, one learns how to create threads and explores the use of mutexes in C.

Key rules of the simulation:
- One or more philosophers sit at a round table with a large bowl of spaghetti in the middle.
- The philosophers alternately eat, think, or sleep.
- While eating, they are not thinking or sleeping; while thinking, they are not eating or sleeping; and while sleeping, they are not eating or thinking.
- There are as many forks on the table as there are philosophers.
- A philosopher must pick up both their right and left forks to eat.
- When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again. The simulation stops when a philosopher dies of starvation.
- Every philosopher needs to eat and should never starve.

## Instructions

### Compilation
To compile the project, navigate to the `philo` directory and run `make`:
```bash
cd philo
make
```
This will produce the `philo` executable.

### Execution
Execute the program with the following arguments:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

#### Arguments:
- `number_of_philosophers`: The number of philosophers and also the number of forks.
- `time_to_die` (in milliseconds): If a philosopher didn't start eating `time_to_die` milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- `time_to_eat` (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
- `time_to_sleep` (in milliseconds): The time a philosopher will spend sleeping.
- `number_of_times_each_philosopher_must_eat` (optional): If all philosophers have eaten at least this many times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

#### Examples

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

## Implementation Details
- **Threading:** Each philosopher is represented by a separate thread using `pthread_create`.
- **Mutexes:** Mutexes (`pthread_mutex_t`) are used to protect the state of each fork and prevent data races.
- **Monitoring:** A separate observer continuously checks if any philosopher has starved or if the meal requirement is fulfilled, ensuring prompt termination of the simulation.
- **Norminette:** The codebase is fully compliant with the 42 C coding standard (Norminette).

## Resources
- [POSIX Threads (pthreads) Programming](https://hpc-tutorials.llnl.gov/posix/)
- [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- **AI Usage**: AI (GitHub Copilot) was utilized during the development of this project primarily for debugging edge cases (such as handling a single philosopher), resolving norminette formatting issues (indentation, forbidden comments, missing headers), confirming thread safety avoiding data-races via mutexes, and assisting in formatting this subject-compliant README file.
