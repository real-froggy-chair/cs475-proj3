/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5	//number of philosophers and forks

//TODO - locks must be declared and initialized here
mutex_t	*locker;
mutex_t *printLock = FALSE;

/**
 * Delay for a random amount of time
 * @param alpha delay factor
 */
void	holdup(int32 alpha)
{
	long delay = rand() * alpha;
	while (delay-- > 0)
		;	//no op
}

/**
 * Eat for a random amount of time
 */
void	eat()
{
	holdup(10000);
}

/**
 * Think for a random amount of time
 */
void	think()
{
	holdup(1000);
}



/**
 * Philosopher's code
 * @param phil_id philosopher's id
 */
void	philosopher(uint32 phil_id)
{
	uint32 	right =  phil_id - 1; //TODO - right fork
	if(phil_id == 0)
		right = N - 1;
	uint32	left  = phil_id; //Left fork

	int		action; //determines 70/30 rand() stuff

	srand(phil_id);

	while (TRUE)
	{
		action = rand() % 10; //0-10
		//kprintf("action == [%d]", action);
		//TODO
		//think 70% of the time
		if(action < 7)
		{
			mutex_lock(&printLock);
			kprintf("Philsopher %d thinking: zzzZZZzzz\n", phil_id);
			mutex_unlock(&printLock);
			think();
			
		}
		else //eat 30% of the time
		{
			//kprintf("What is happening [%u] [%u]\n",locker[left], locker[right]); 
			//attempt to lock both forks
			//if(locker[left] == FALSE && locker[right] == FALSE)
			//{
				
				mutex_lock(&locker[left]);
				mutex_lock(&locker[right]);
				mutex_lock(&printLock);
				kprintf("Philsopher %d eating: nom nom nom\n", phil_id);
				mutex_unlock(&printLock);
				eat();
				mutex_unlock(&locker[left]);
				mutex_unlock(&locker[right]);
				
			//}
		}
	}
}

int	main(uint32 argc, uint32 *argv)
{
	*locker = (mutex_t*) malloc(sizeof(mutex_t) * N); //How do you initialize a dynamic array globally??
	for(int i = 0; i < N; i++)
	{
		locker[i] = FALSE;
	}

	//do not change
	ready(create((void*) philosopher, INITSTK, 15, "Ph1", 1, 0), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph2", 1, 1), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph3", 1, 2), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph4", 1, 3), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph5", 1, 4), FALSE);

	free(locker, sizeof(mutex_t) * N); //please don't break anything
	return 0;
}
