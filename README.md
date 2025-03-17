# Philosophers

## 🌟 Project Overview
**Philosophers** is a multithreading and synchronization project that simulates the dining philosophers problem using threads and mutexes. The challenge is to avoid common issues like deadlocks and resource starvation as multiple philosophers concurrently attempt to eat, think, and sleep.

## 🚀 How to Use

### 📋 Requirements
- Unix/Linux operating system.
- C compiler (CC).
- Basic understanding of multithreading concepts.

### 📖 Instructions

1. **Clone the repository:**
   ```bash
   git clone https://github.com/curtyraissa/philosophers.git
   cd philosophers
   cd philo
   ```

2. **Compile the project:**
   ```bash
   make
   ```

3. **Run the program:**  Provide arguments for the number of philosophers and other simulation parameters. Example:

| Example | Expected Result |
| :-- | :-- |
| `./philo 4 500 200 1.2`           | Invalid argument.                                              |
| `./philo 4 0 200 200`             | Invalid argument.                                              |
| `./philo 4 -500 200 200`          | Invalid argument.                                              |
| `./philo 4 214748364732 200 200`  | Invalid argument.                                              |
| `./philo 1 200 200 200`           | Philosopher 1 takes a fork and dies after 200 ms.              |
| `./philo 4 500 200 2147483647`    | A philosopher dies after 500 ms                                |
| `./philo 4 200 210 200`           | A philosopher dies, it should display the death before 210 ms. |
| `./philo 4 310 200 200`           | A philosopher dies.                                            |
| `./philo 5 800 200 200 7`         | The program stops when each philosopher has eaten 7 times.     |
| `./philo 5 800 200 200`           | No philosopher dies.                                           |
| `./philo 4 2147483647 200 200`    | No philosopher dies.                                           |
| `./philo 5 800 200 150`           | No philosopher dies.                                           |
| `./philo 3 610 200 80`            | No philosopher dies.                                           |
| `./philo 2 800 200 200`           | No philosopher dies.                                           |
| `./philo 4 410 200 200`           | No philosopher dies.                                           |

   The parameters represent the number of philosophers, time to die, time to eat, and time to sleep, respectively.
   
5. Observe the simulation: Watch as philosophers pick up forks, eat, and think according to the rules of the simulation.


### 🧹 Cleanup
To clean up the compiled files:
   ```bash
    make fclean
   ```

### 🛠 Technologies
   ```
C Language: Used to handle all logic related to thread management and synchronization.  
Pthreads: Utilized for creating and managing threads.  
Mutexes: Ensures exclusive access to resources (forks).  
Norminette: Ensures code adheres to the 42 School's norm standards.  
   ```
---

## 💬 &nbsp;Contacts
<img align="left" src="https://avatars.githubusercontent.com/curtyraissa?size=100">

Made by [Raissa Curty](https://github.com/curtyraissa)!
