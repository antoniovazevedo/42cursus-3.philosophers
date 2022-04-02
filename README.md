# 🤔 philosophers 🤔

## Research
‣ [Data race](https://riptutorial.com/c/example/2622/data-race)

‣ [Mutex Locks](https://www.thegeekstuff.com/2012/05/c-mutex-examples/)

## Arguments
- number_of_philosophers (1+)
- time_to_die (in ms)
- time_to_eat (in ms)
- time_to_sleep (in ms)
- number_of_times_each_philosopher_must_eat _(optional)_

## Activities
Philosophers alternate between:
- eating
- sleeping
- thinking

The simulation stops when all philosophers have eaten at least `number_of_times_each_philosopher_must_eat` times (or if this is not specified, it stops when a philosopher dies).

## Structure
### main struct
- input data (arguments)
- philosophers (array of `philosopher` structs)

### philosopher struct
- `int` number
- `enum` state
- `struct` *left_fork
- `struct` *right_fork

### fork struct
- `enum` state
- mutex

## Input validation
- `number_of_philosophers` must be >= 1
- `time_to_die`, `time_to_eat` and `time_to_sleep` must be >= 0
- `number_of_times_each_philosopher_must_eat` (optional) must be >= 0

## Initialization
- Create main struct
- Create fork struct for each fork (same as philosopher count)
	- init fork mutex
- Create philosopher struct for each philosopher
	- include pointer for left and right forks
- Start a thread for each philosopher
