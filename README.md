*This project has been created as part of the 42 curriculum by kkhant-z.*

# Description

**philosophers** is a solution to the classic *dining philosophers* problem, written in C with POSIX threads and mutexes.

A number of philosophers sit at a round table with a bowl of spaghetti in the middle. There is one fork between each pair of neighbours, and a philosopher needs both the left and the right fork to eat. Each philosopher repeatedly eats, sleeps and thinks. If a philosopher goes `time_to_die` milliseconds without starting a meal, they die and the simulation stops. The goal is to keep everyone alive for as long as possible, without data races or deadlocks.

## How it works

- **One thread per philosopher**, plus one **observer thread** that watches for deaths and for everyone having eaten enough.
- **One mutex per fork.** Even-numbered philosophers pick up their left fork first and odd-numbered ones their right fork first, which prevents a circular wait (deadlock).
- **Synchronised start.** The observer sets a common start time and every philosopher's initial death deadline before releasing the threads, so all philosophers start from the same instant.
- **Staggering.** Odd-numbered philosophers wait `time_to_eat` before their first meal. When the number of philosophers is odd, each philosopher also thinks for `2 * time_to_eat - time_to_sleep` ms after sleeping, so a neighbour always gets a turn and nobody starves.
- **Precise sleeping.** Instead of one long `usleep`, sleeps are done in short steps against `gettimeofday`. This avoids drift building up over time and lets a sleeping philosopher stop as soon as someone dies.
- **Protected output.** All state changes are printed under a mutex, and nothing is printed after a death is reported. A death is printed within a few milliseconds of it happening.

# Instructions

## Compilation

```sh
make        # builds ./philo
make clean  # removes object files
make fclean # removes object files and ./philo
make re     # rebuilds from scratch
```

## Usage

```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argument | Meaning |
|---|---|
| `number_of_philosophers` | Number of philosophers, and also the number of forks |
| `time_to_die` (ms) | Maximum time between the start of two meals (or since the start of the simulation) before a philosopher dies |
| `time_to_eat` (ms) | Time it takes to eat, holding both forks |
| `time_to_sleep` (ms) | Time spent sleeping after eating |
| `number_of_times_each_philosopher_must_eat` | Optional. The simulation stops once every philosopher has eaten at least this many times |

All arguments must be positive integers.

Each state change is printed as `timestamp_in_ms philosopher_number action`:

```
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
800 3 died
```

## Examples

```sh
./philo 1 800 200 200      # the only philosopher has one fork and dies at 800
./philo 5 800 200 200      # nobody should die
./philo 5 800 200 200 7    # stops once everyone has eaten 7 times
./philo 4 410 200 200      # nobody should die
./philo 4 310 200 100      # a philosopher dies at about 310
```

## Checking for data races and leaks

Helgrind and DRD (both part of Valgrind) report data races, lock-order problems and misuse of the pthread API. Run them with a meal limit so the simulation ends on its own. Both tools slow the program down a lot, so use a small number of philosophers and generous times; a death reported under them doesn't mean the timing is wrong.

```sh
valgrind --tool=helgrind ./philo 4 800 200 200 3
valgrind --tool=drd ./philo 4 800 200 200 3
```

A clean run ends with `ERROR SUMMARY: 0 errors from 0 contexts`.

To check for memory leaks, including when the simulation ends with a death:

```sh
valgrind --leak-check=full --show-leak-kinds=all ./philo 5 800 200 200 3
valgrind --leak-check=full --show-leak-kinds=all ./philo 4 310 200 100
```

A clean run shows `in use at exit: 0 bytes in 0 blocks`.

ThreadSanitizer is a faster race detector built into the compiler. It needs a separate build:

```sh
cc -Wall -Wextra -Werror -g -fsanitize=thread -Iinclude src/*.c -o philo_tsan -lpthread
./philo_tsan 5 800 200 200 5
```

No `WARNING: ThreadSanitizer: data race` in the output means no race was found. Don't run a ThreadSanitizer build under Valgrind.

# Resources

- [Mutex vs Semaphore](https://www.geeksforgeeks.org/operating-systems/mutex-vs-semaphore/)
- [Dining philosophers problem (Wikipedia)](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [`pthread_create(3)`](https://man7.org/linux/man-pages/man3/pthread_create.3.html), [`pthread_mutex_lock(3p)`](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html), [`gettimeofday(2)`](https://man7.org/linux/man-pages/man2/gettimeofday.2.html)

## AI usage

Claude (Anthropic) was used as a reviewing and testing assistant:

- reviewing the mandatory part and pointing out the remaining timing bugs (start-time synchronisation, `usleep` drift, starvation with an odd number of philosophers);
- running test cases, ThreadSanitizer, Valgrind and Helgrind to check for deaths, data races and leaks;
- drafting this README.

The code itself was written by me, and every suggestion was checked and tested before being kept.
