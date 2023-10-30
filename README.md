# Philosophers
How to feed and put to bed philosophers alternatively without them dying in the meanwhile? This repo contains my implementation of the dining philosophers problem: Philosophers are sitting around a table to have dinner. In front of them are two forks, and philosophers need to grab two forks to be able to eat. However each fork is shared by two philosophers which means that philosophers sitting next to each other can't eat in the same time. Each philosopher is represented by a thread, and all threads are synchronised to execute a routine avoiding to step in each others way (avoiding data races and dead locks). Find a detail description here: [subject.pdf](https://github.com/Axel-ex/philosophers/blob/main/subject.pdf)

## Usage
`git clone` this project `cd` into it and `make`. for debug formating and colored output `make MODE=debug`.
the program is executed as so:

```shell
./philo <nb_philos> <time_to_die> <time_to_eat> <time_to_sleep> (optional) <nb_of_meal_to_eat>
```

The program will then display the actions executed by the philosophers and simulation will stop once one philosopher will die, once all of them will have eat enough (if nb_of_meal_to_eat is specified), or will never stop if `time_to_die` > `time_to_eat` + `time_to_eat`.