/*
Laboratory OS 2 / Exercise 2 / Question 2 / 2021-22
Name: Athanasiou Vasileios Evangelos
Student ID: 19390005
Compilation Command: gcc -o semaphores semaphores.c -lpthread -lrt
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <semaphore.h>

/************************************************************************ Declaration of Semaphores *********************************************************************************************/
sem_t sem1, sem2, sem3;                                                   // Declaration of three variables of type "sem_t" (imported from the "POSIX semaphores" library (line 12)), i.e., the three semaphores that will be created (lines 28, 33, 38).
/***********************************************************************************************************************************************************************************************/

/************************************************************************ Declaration of the critical sections of the three "threads" *********************************************************************/
void *thread1 (void *);                                                   // Declaration of the "thread1" function (critical section), which will be called by the 1st "thread" that will be created, and it is implemented in lines 97-113.
void *thread2 (void *);                                                   // Declaration of the "thread2" function (critical section), which will be called by the 2nd "thread" that will be created, and it is implemented in lines 117-134.
void *thread3 (void *);                                                   // Declaration of the "thread3" function (critical section), which will be called by the 3rd "thread" that will be created, and it is implemented in lines 138-155.
/***********************************************************************************************************************************************************************************************/

int main (int argc, char *argv[])
{
    pthread_t pthread1, pthread2, pthread3;                               // Declaration of three variables of type "pthread_t" (imported from the "POSIX Threads" library (lines 10-11)), i.e., the three "threads" that will be created (lines 44, 49, 54).
    
    if (sem_init(&sem1, 0, 0) < 0)                                        /* Call of the "sem_init()" function imported from the "POSIX semaphores" library (line 12), which creates the semaphore "sem1" (not shared with another process) and initializes it to 0. An error return value is checked. */
    {
        perror("sem_init() failed to execute");                           // Prints an error message to "stderr" for the failure of "sem_init()".
        exit(1);                                                          // The process terminates with "exit value" 1.
    }
    if (sem_init(&sem2, 0, 0) < 0)                                        /* Similar to the above, the semaphore "sem2" is created and initialized to 0. */
    {
        perror("sem_init() failed to execute");
        exit(1);
    }
    if (sem_init(&sem3, 0, 1) < 0)                                        /* "sem3" is created and initialized to 1. */
    {
        perror("sem_init() failed to execute");
        exit(1);
    }
        
    if (pthread_create(&pthread1, NULL, &thread1, NULL) < 0)              /* Calls the "pthread_create()" function from the "POSIX Threads" library (lines 10-11), creating the 1st "thread" (pthread1), which will call the "thread1" function (critical section, lines 97-113) with no parameters. Error return is checked. */
    {
        perror("pthread_create() failed to execute");                    
        exit(1);                                                          
    }
    if (pthread_create(&pthread2, NULL, &thread2, NULL) < 0)              /* Creates the 2nd "thread" (pthread2), which will call "thread2" (lines 117-134) with no parameters. */
    {
        perror("pthread_create() failed to execute");
        exit(1);
    }
    if (pthread_create(&pthread3, NULL, &thread3, NULL) < 0)              /* Creates the 3rd "thread" (pthread3), which will call "thread3" (lines 138-155) with no parameters. */
    {
        perror("pthread_create() failed to execute");
        exit(1);
    }

    if (pthread_join(pthread1, NULL) < 0)                                 /* Calls "pthread_join()" to synchronize the 1st thread (pthread1) and check for error return. */
    {
        perror("pthread_join() failed to execute");
        exit(1);
    }
    if (pthread_join(pthread2, NULL) < 0)                                 /* Similar join for 2nd thread. */
    {
        perror("pthread_join() failed to execute");
        exit(1);
    }
    if (pthread_join(pthread3, NULL) < 0)                                 /* Similar join for 3rd thread. */
    {
        perror("pthread_join() failed to execute");
        exit(1);
    }
    
    if (sem_destroy(&sem1) < 0)                                           /* Destroys semaphore "sem1" to free memory, error checked. */
    {
        perror("sem_destroy() failed to execute");
        exit(1);
    } 
    if (sem_destroy(&sem2) < 0)                                           /* Destroys semaphore "sem2". */
    {
        perror("sem_destroy() failed to execute");
        exit(1);
    }
    if (sem_destroy(&sem3) < 0)                                           /* Destroys semaphore "sem3". */
    {
        perror("sem_destroy() failed to execute");
        exit(1);
    }

    return 0;
}

/************************************************************************* Critical section of "pthread1" ****************************************************************************************/
void *thread1(void *parameter)
{
    while (1)                                                              /* Infinite loop */
    {
        if (sem_wait(&sem3) < 0)                                           /* Calls "sem_wait()" from the "POSIX semaphores" library (line 12), which decreases the value of the semaphore "sem3" by 1, if it is non-zero. If the semaphore value is 0, it waits until the value becomes non-zero. Since "sem3" was initialized to 1 in line 37, calling "sem_wait()" decreases it by 1, setting it to 0, allowing the rest of the critical section to execute (lines 101-112). When "sem_wait()" is called again, due to the infinite loop, the semaphore will wait until its value is incremented in the critical section of "pthread3" (lines 139-155) with a "sem_post()" (also imported from the "POSIX semaphores" library (line 12)), which increases "sem3" by 1 in line 148. Error return from "sem_wait()" is checked. */
        {
            perror("sem_wait() failed to execute");                       
            exit(1);                                                       
        }
        printf("What A ");                                                  // Prints "What A" to "stdout".
        if (sem_post(&sem1) < 0)                                            /* Calls "sem_post()" from the "POSIX semaphores" library (line 12), which increases the value of the semaphore "sem1" by 1. "sem1" was initialized to 0 in line 28, so this increases it to 1, allowing the critical section of "pthread2" (lines 122-133) to proceed, which was waiting due to a "sem_wait()" call in line 121. Error return from "sem_post()" is checked. */
        {
            perror("sem_post() failed to execute");                       
            exit(1);                                                       
        }
    }
    pthread_exit(NULL);                                                     // The "thread" terminates its operation.
}
/***********************************************************************************************************************************************************************************************/

/************************************************************************** Critical section of "pthread2" ****************************************************************************************/
void *thread2 (void *parameter)
{   
    while (1)                                                                /* Infinite loop */
    { 
        if (sem_wait (&sem1) < 0)                                           /* Call to the "sem_wait()" function, imported from the "POSIX semaphores" library (line 12), which decreases the value of the semaphore "sem1" by 1 if it is non-zero. If the value of the semaphore "sem1" is 0, it waits until the value becomes non-zero so it can be decreased. From the initialization of "sem1" in line 28, which is set to 0, we can see that calling "sem_wait()" will put it in waiting until its value becomes non-zero, allowing it to be decreased by 1 and exit the wait. This is achieved in the critical section of "pthread1" (lines 97-113) with the call to the "sem_post()" function (also imported from the "POSIX semaphores" library (line 12)) in line 106, which increases the value of "sem1" by 1. Thus, "sem_wait()" will decrease the value of "sem1" by 1 and the rest of the critical section of "pthread2" (lines 122-133) will be executed, entering the wait again due to the infinite loop and exiting when its value is increased by 1 again in line 106. Additionally, the return value of "sem_wait()" is checked for errors. */
        {
            perror ("sem_wait () failed to execute");                       // Prints an error message to "stderr" for the failure of "sem_wait ()".
            exit (1);                                                       // The process terminates with "exit value" 1.
        }
        printf ("Wonderful ");                                              // Prints the message "Wonderful " to "stdout".
        if (sem_post (&sem2) < 0)                                           /* Call to the "sem_post ()" function, imported from the "POSIX semaphores" library (line 12), which increases the value of the semaphore "sem2" by 1. From the initialization of "sem2" in line 33, which is set to 0, we can see that by calling "sem_post ()", its value will increase by 1, so the new value will be 1, and thus, the rest of the critical section of "pthread3" (lines 143-154) will be executed, which was in waiting due to the call to "sem_wait ()" (also imported from the "POSIX semaphores" library (line 12)) in line 142 and the initialization of "sem2" to 0 in line 33. The return value of "sem_post ()" is also checked for errors. */
        {
            perror ("sem_post () failed to execute");                       // Prints an error message to "stderr" for the failure of "sem_post ()".
            exit (1);                                                       // The process terminates with "exit value" 1.
        }
    }
    pthread_exit (NULL);                                                    // The "thread" terminates its operation.
}
/***********************************************************************************************************************************************************************************************/

/************************************************************************** Critical section of "pthread3" ***************************************************************************************/
void *thread3 (void *parameter)
{
    while (1)                                                               /* Infinite loop */
    { 
        if (sem_wait (&sem2) < 0)                                           /* Call to the "sem_wait ()" function, imported from the "POSIX semaphores" library (line 12), which decreases the value of the semaphore "sem2" by 1 if it is non-zero. If the value of the semaphore "sem2" is 0, it waits until the value becomes non-zero so it can be decreased. From the initialization of "sem2" in line 33, which is set to 0, we can see that calling "sem_wait ()" will put it in waiting until its value becomes non-zero, allowing it to be decreased by 1 and exit the wait. This is achieved in the critical section of "pthread2" (lines 118-134) with the call to the "sem_post ()" function (also imported from the "POSIX semaphores" library (line 12)) in line 127, which increases the value of "sem2" by 1. Thus, "sem_wait ()" will decrease the value of "sem2" by 1 and the rest of the critical section of "pthread3" (lines 143-154) will be executed, entering the wait again due to the infinite loop and exiting when its value is increased by 1 again in line 127. The return value of "sem_wait ()" is also checked for errors. */
        {
            perror ("sem_wait () failed to execute");                       // Prints an error message to "stderr" for the failure of "sem_wait ()".
            exit (1);                                                       // The process terminates with "exit value" 1.
        }
        printf ("World! ");                                                 // Prints the message "World! " to "stdout".
        if (sem_post (&sem3) < 0)                                           /* Call to the "sem_post ()" function, imported from the "POSIX semaphores" library (line 12), which increases the value of the semaphore "sem3" by 1. From the initialization of "sem3" in line 38, which is set to 1, and the call to "sem_wait ()" in the critical section of "pthread1" (lines 97-113) in line 100, and thus the reduction of "sem3" by 1, which will set its value to 0, we can see that calling "sem_post ()" will increase the value of "sem3" by 1, so its new value will be 1 again, and thus the rest of the critical section of "pthread1" (lines 101-113) will be executed, which was in waiting due to the call to "sem_wait ()" (also imported from the "POSIX semaphores" library (line 12)) in line 100 in the loop and the previously mentioned procedure for changing the content of "sem3". The return value of "sem_post ()" is also checked for errors. */
        {
            perror ("sem_post () failed to execute");                       // Prints an error message to "stderr" for the failure of "sem_post ()".
            exit (1);                                                       // The process terminates with "exit value" 1.
        }
    }
    pthread_exit (NULL);                                                    // The "thread" terminates its operation.
}
/***********************************************************************************************************************************************************************************************/

/*  SAMPLE RUNS
    
    #1 ./semaphores
    What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World!
	What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World!
	What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World! 
	What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World! 
	What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World!
	What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World! 
	What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World! 
	What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World!
	What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World!
	What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World! 
	What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World! 
	What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World! What A Wonderful World!...

    COMMENTS
    
    With the infinite loops in the critical sections of the three "threads", parts of the code are left unexecuted since the loops will not terminate by the process
	itself, but only by user intervention to manually terminate the program. Specifically, the "threads" will never terminate (the "pthread_exit()" function imported
	from the "POSIX Threads" library (lines 10-11) is located outside the loops of the critical sections of the three "threads" in lines 112, 133, 154 respectively),
	so they will not be synchronized for their memory deallocation with the call to "pthread_join()" (also imported from the "POSIX Threads" library (lines 10-11))
	in lines 60, 65, 70. Additionally, the three semaphores will not be deallocated from memory with the call to "sem_destroy()" (imported from the "POSIX semaphores"
	library (line 12) in lines 76, 81, 86 respectively. Thus, the process will run indefinitely, and its termination will only happen with user intervention.
    
*/

    
