/*
Lab OS 2 / Exercise 2 / Question 2 / 2021-22
Name: Athanasiou Vasileios Evangelos
Student ID: 19390005
Compilation Command: gcc -o condition_vars condition_vars.c -pthread 
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>

/************************************************************************ Declaration of shared resources **********************************************************************************************/
int cnt_signal = 1;                                                       // Declaration and initialization of the global-shared variable with the value 1 (trigger for printing the string "What A "), which indicates the thread ID that must check if it corresponds to its own before executing its critical section (having locked the "mutex", of course). The value 1 is the ID for the 1st thread, 2 for the 2nd, and 3 for the 3rd thread.
int cnt_wait = 0;                                                         // Declaration and initialization of the global-shared variable with the value 0, which counts the number of threads waiting using a "condition variable".
/***********************************************************************************************************************************************************************************************/

/************************************************************************ Declaration and static initialization of the "mutex"  *************************************************************************/
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;                          // Declaration and static initialization of a "pthread_mutex_t" variable with the constant "PTHREAD_MUTEX_INITIALIZER", which is imported from the "POSIX Threads" library (line 10), i.e., the "mutex" (lines 93-114, 137-158, 181-202 for the 1st, 2nd, and 3rd threads respectively) used to protect the shared resources "cnt_signal, cnt_wait" (lines 14-15) in the critical section of the threads from simultaneous access by two or more threads.
/***********************************************************************************************************************************************************************************************/

/************************************************************************ Declaration and static initialization of the "condition variable" *************************************************************/
pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;                       // Declaration and static initialization of a "pthread_cond_t" variable with the constant "PTHREAD_COND_INITIALIZER", imported from the "POSIX Threads" library (lines 10-11), i.e., a "condition variable" that achieves synchronization between threads by putting one or more threads to wait while releasing the "mutex" for other threads to use. It can wake the waiting threads with a signal. The combination of waiting and waking between threads is determined by the content of the global-shared variables (lines 13-14) that will be explained in the corresponding critical sections of the threads (lines 84-123, 128-167, 172-211 for the 1st, 2nd, and 3rd threads respectively).
/***********************************************************************************************************************************************************************************************/

/************************************************************************ Declaration of critical sections of the three "threads" *********************************************************************/
void *thread1 (void *);                                                   // Declaration of the "thread1" function (critical section), which will be called by the 1st thread that will be created, and it is implemented in lines 84-123.
void *thread2 (void *);                                                   // Declaration of the "thread2" function (critical section), which will be called by the 2nd thread that will be created, and it is implemented in lines 128-167.
void *thread3 (void *);                                                   // Declaration of the "thread3" function (critical section), which will be called by the 3rd thread that will be created, and it is implemented in lines 172-211.
/***********************************************************************************************************************************************************************************************/

int main (int argc, char *argv[])
{
    pthread_t pthread1, pthread2, pthread3;                                // Declaration of three variables of type "pthread_t" (imported from the "POSIX Threads" library (lines 10-11)), i.e., the three threads that will be created (lines 36, 41, 46).
        
    if (pthread_create (&pthread1, NULL, &thread1, NULL) < 0)              /* Call to the "pthread_create ()" function imported from the "POSIX Threads" library (lines 10-11), for creating the 1st thread (pthread1), which will call the "thread1" function (critical section, lines 84-123) without parameters, and checking for an error return value. */
    {
        perror ("pthread_create () failed to execute");                    // Prints an error message to "stderr" for the failure of "pthread_create ()".
        exit (1);                                                          // The process terminates with "exit value" 1.
    }
    if (pthread_create (&pthread2, NULL, &thread2, NULL) < 0)              /* Call to the "pthread_create ()" function imported from the "POSIX Threads" library (lines 10-11), for creating the 2nd thread (pthread2), which will call the "thread2" function (critical section, lines 128-167) without parameters, and checking for an error return value. */
    {
        perror ("pthread_create () failed to execute");                    // Prints an error message to "stderr" for the failure of "pthread_create ()".
        exit (1);                                                          // The process terminates with "exit value" 1.
    }
    if (pthread_create (&pthread3, NULL, &thread3, NULL) < 0)              /* Call to the "pthread_create ()" function imported from the "POSIX Threads" library (lines 10-11), for creating the 3rd thread (pthread3), which will call the "thread3" function (critical section, lines 172-211) without parameters, and checking for an error return value. */
    {
        perror ("pthread_create () failed to execute");                    // Prints an error message to "stderr" for the failure of "pthread_create ()".
        exit (1);                                                          // The process terminates with "exit value" 1.
    }

    if (pthread_join (pthread1, NULL) < 0)                                 /* Call to the "pthread_join ()" function imported from the "POSIX Threads" library (lines 10-11), for synchronizing the 1st thread (pthread1) to release memory, and checking for an error return value. */
    {
        perror ("pthread_join () failed to execute");                      // Prints an error message to "stderr" for the failure of "pthread_join ()".
        exit (1);                                                          // The process terminates with "exit value" 1.
    }
    if (pthread_join (pthread2, NULL) < 0)                                 /* Call to the "pthread_join ()" function imported from the "POSIX Threads" library (lines 10-11), for synchronizing the 2nd thread (pthread2) to release memory, and checking for an error return value. */
    {
        perror ("pthread_join () failed to execute");                      // Prints an error message to "stderr" for the failure of "pthread_join ()".
        exit (1);                                                          // The process terminates with "exit value" 1.
    }
    if (pthread_join (pthread3, NULL) < 0)                                 /* Call to the "pthread_join ()" function imported from the "POSIX Threads" library (lines 10-11), for synchronizing the 3rd thread (pthread3) to release memory, and checking for an error return value. */
    {
        perror ("pthread_join () failed to execute");                      // Prints an error message to "stderr" for the failure of "pthread_join ()".
        exit (1);                                                          // The process terminates with "exit value" 1.
    }
    
    if (pthread_mutex_destroy (&mut) < 0)                                  /* Call to the "pthread_mutex_destroy ()" function imported from the "POSIX Threads" library (lines 10-11), for destroying the "mutex" to release memory (lines 93-114, 137-158, 181-202 for the 1st, 2nd, and 3rd threads respectively), which was created in line 19 to protect the shared resources from simultaneous use by two or more threads, and checking for an error return value. */
    {
        perror ("pthread_mutex_destroy () failed to execute");             // Prints an error message to "stderr" for the failure of "pthread_mutex_destroy ()".
        exit (1);                                                          // The process terminates with "exit value" 1.
    }
    if (pthread_cond_destroy (&cond_var) < 0)                              /* Call to the "pthread_cond_destroy ()" function imported from the "POSIX Threads" library (lines 10-11), for destroying the "condition variable" to release memory, which was created in line 23 to synchronize the threads. */
    {
        perror ("pthread_cond_destroy () failed to execute");               // Prints an error message to "stderr" for the failure of "pthread_cond_destroy ()".
        exit (1);                                                           // The process terminates with "exit value" 1.
    }

    return 0;
}

/************************************************************************** Critical section of "pthread1" ****************************************************************************************/
void *thread1 (void *parameter)
{
    while (1)                                                               /* Infinite loop */
    {
        if (pthread_mutex_lock (&mut) < 0)                                  /* Call to the "pthread_mutex_lock ()" function from the "POSIX Threads" library (lines 10-11), to lock the "mutex" (lines 93-114) which was created to protect shared resources in the critical section of "pthread1" from simultaneous access by two or more threads, and check for an error return value. */
        {
            perror ("pthread_mutex_lock () failed to execute");             // Prints an error message to "stderr" for the failure of "pthread_mutex_lock ()".
            exit (1);                                                       // The process terminates with "exit value" 1.
        }
/************************************************************************** Mutex ****************************************************************************************************************/        
        while (cnt_signal != 1)                                             /* Loop to check whether "cnt_signal" contains the ID value corresponding to the 1st thread (1), allowing "pthread1" to continue executing its critical section (cnt_signal == 1), or not (cnt_signal != 1). */
        {
            cnt_wait++;                                                     // Increment the global-shared variable "cnt_wait" by 1, indicating that at least one thread is waiting, using a "condition variable".
            if (pthread_cond_wait (&cond_var, &mut) < 0)                    /* Call to the "pthread_cond_wait ()" function from the "POSIX Threads" library (lines 10-11), putting "pthread1" in wait and simultaneously releasing the "mutex" for use by another thread. The loop will continue while "cnt_signal" does not contain the ID value corresponding to the 1st thread (1). Thus, the thread will be trapped in the loop with continuous waits and loss of control over the "mutex" until "cnt_signal" "gives the signal" (change of its value from the critical section of "pthread3" (lines 172-211)) to "release" the thread from the loop, i.e., containing the ID value corresponding to the 1st thread (1). The return value of "pthread_cond_wait ()" is also checked for errors. */
            {
                perror ("pthread_cond_wait () failed to execute");          // Prints an error message to "stderr" for the failure of "pthread_cond_wait ()".
                exit (1);                                                   // The process terminates with "exit value" 1.
            }
        }
        printf ("What A ");                                                 // Prints "What A" to "stdout".
        if (cnt_wait > 0)                                                   /* Check if one or more threads are already waiting */
        {
            cnt_signal = 2;                                                 // Change the ID value to the one corresponding to the 2nd thread (2) (trigger for the next output, the string "Wonderful ").
            if (pthread_cond_broadcast (&cond_var) < 0)                     /* Call to the "pthread_cond_broadcast ()" function from the "POSIX Threads" library (lines 10-11), waking all threads waiting for a signal, ensured by the check in line 103. The return value of "pthread_cond_broadcast ()" is also checked for errors. */
            {
                perror ("pthread_cond_broadcast () failed to execute");     // Prints an error message to "stderr" for the failure of "pthread_cond_broadcast ()".
                exit (1);                                                   // The process terminates with "exit value" 1.
            }
            cnt_wait = 0;                                                   // Reset the count of threads in wait, since the call to "pthread_cond_broadcast ()" in line 106 has already occurred.
        } 
        else                                                                /* No threads are in wait */
            cnt_signal = 2;                                                 // Since no threads are in wait, simply change the ID value to the one corresponding to the 2nd thread (2) (trigger for the next output, the string "Wonderful ").
/***********************************************************************************************************************************************************************************************/
        if (pthread_mutex_unlock (&mut) < 0)                                /* Call to the "pthread_mutex_unlock ()" function from the "POSIX Threads" library (lines 10-11), to unlock the "mutex" (lines 93-114) which was created to protect shared resources in the critical section from simultaneous use by two or more threads, and check for an error return value. */
        {
            perror ("pthread_mutex_unlock () failed to execute");           // Prints an error message to "stderr" for the failure of "pthread_mutex_unlock ()".
            exit (1);                                                       // The process terminates with "exit value" 1.
        } 
    }
    pthread_exit (NULL);                                                    // The thread terminates its operation.
}
/***********************************************************************************************************************************************************************************************/

/************************************************************************** Critical section of "pthread2" ***************************************************************************************/
void *thread2 (void *parameter)
{
    while (1)                                                               /* Infinite loop */
    {
        if (pthread_mutex_lock (&mut) < 0)                                  /* Call to the "pthread_mutex_lock ()" function from the "POSIX Threads" library (lines 10-11), to lock the "mutex" (lines 137-158) which was created to protect shared resources in the critical section of "pthread2" from simultaneous access by two or more threads, and check for an error return value. */
        {
            perror ("pthread_mutex_lock () failed to execute");             // Prints an error message to "stderr" for the failure of "pthread_mutex_destroy ()".
            exit (1);                                                       // The process terminates with "exit value" 1.
        }
/************************************************************************** Mutex ***************************************************************************************************************/
        while (cnt_signal != 2)                                             /* Loop to check whether "cnt_signal" contains the ID value corresponding to the 2nd thread (2), allowing "pthread2" to continue executing its critical section (cnt_signal == 2), or not (cnt_signal != 2). */
        {
            cnt_wait++;                                                     // Increment the global-shared variable "cnt_wait" by 1, indicating that at least one thread is waiting, using a "condition variable".
            if (pthread_cond_wait (&cond_var, &mut) < 0)                    /* Call to the "pthread_cond_wait ()" function from the "POSIX Threads" library (lines 10-11), putting "pthread2" in wait and simultaneously releasing the "mutex" for use by another thread. The loop will continue while "cnt_signal" does not contain the ID value corresponding to the 2nd thread (2). Thus, the thread will be trapped in the loop with continuous waits and loss of control over the "mutex" until "cnt_signal" "gives the signal" (change of its value from the critical section of "pthread1" (lines 84-123)) to "release" the thread from the loop, i.e., containing the ID value corresponding to the 2nd thread (2). The return value of "pthread_cond_wait ()" is also checked for errors. */
            {
                perror ("pthread_cond_wait () failed to execute");         // Prints an error message to "stderr" for the failure of "pthread_cond_wait ()".
                exit (1);                                                  // The process terminates with "exit value" 1.
            }       
        }
        printf ("Wonderful ");                                             // Prints "Wonderful " to "stdout".
        if (cnt_wait > 0)                                                  /* Check if one or more threads are already waiting */
        {
            cnt_signal = 3;                                                // Change the ID value to the one corresponding to the 3rd thread (3) (trigger for the next output, the string "World! ").
            if (pthread_cond_broadcast (&cond_var) < 0)                    /* Call to the "pthread_cond_broadcast ()" function from the "POSIX Threads" library (lines 10-11), waking all threads waiting for a signal, ensured by the check in line 147. The return value of "pthread_cond_broadcast ()" is also checked for errors. */
            {
                perror ("pthread_cond_broadcast () failed to execute");    // Prints an error message to "stderr" for the failure of "pthread_cond_broadcast ()".
                exit (1);                                                  // The process terminates with "exit value" 1.
            }
            cnt_wait = 0;                                                  // Reset the count of threads in wait, since the call to "pthread_cond_broadcast ()" in line 150 has already occurred.
        }
        else                                                               /* No threads are in wait */
            cnt_signal = 3;                                                // Since no threads are in wait, simply change the ID value to the one corresponding to the 3rd thread (3) (trigger for the next output, the string "World! ").
/***********************************************************************************************************************************************************************************************/        
        if (pthread_mutex_unlock (&mut) < 0)                               /* Call to the "pthread_mutex_unlock ()" function from the "POSIX Threads" library (lines 10-11), to unlock the "mutex" (lines 137-158) which was created to protect shared resources in the critical section from simultaneous use by two or more threads, and check for an error return value. */
        {
            perror ("pthread_mutex_unlock () failed to execute");          // Prints an error message to "stderr" for the failure of "pthread_mutex_unlock ()".
            exit (1);                                                      // The process terminates with "exit value" 1.
        }
    }
    pthread_exit (NULL);                                                   // The thread terminates its operation.
}
/***********************************************************************************************************************************************************************************************/

/************************************************************************* Critical section of "pthread3" ****************************************************************************************/
void *thread3 (void *parameter)
{
    while (1)                                                              /* Infinite loop */
    {
        if (pthread_mutex_lock (&mut) < 0)                                 /* Call to the "pthread_mutex_lock ()" function from the "POSIX Threads" library (lines 10-11), to lock the "mutex" (lines 181-202) which was created to protect shared resources in the critical section of "pthread3" from simultaneous access by two or more threads, and check for an error return value. */
        {
            perror ("pthread_mutex_lock () failed to execute");            // Prints an error message to "stderr" for the failure of "pthread_mutex_lock ()".
            exit (1);                                                      // The process terminates with "exit value" 1.
        }
/******************************************************************************* Mutex *********************************************************************************************************/
        while (cnt_signal != 3)                                            /* Loop to check whether "cnt_signal" contains the ID value corresponding to the 3rd thread (3), allowing "pthread3" to continue executing its critical section (cnt_signal == 3), or not (cnt_signal != 3). */
        {
            cnt_wait++;                                                    // Increment the global-shared variable "cnt_wait" by 1, indicating that at least one thread is waiting, using a "condition variable".
            if (pthread_cond_wait (&cond_var, &mut) < 0)                   /* Call to the "pthread_cond_wait ()" function from the "POSIX Threads" library (lines 10-11), putting "pthread3" in wait and simultaneously releasing the "mutex" for use by another thread. The loop will continue while "cnt_signal" does not contain the ID value corresponding to the 3rd thread (3). Thus, the thread will be trapped in the loop with continuous waits and loss of control over the "mutex" until "cnt_signal" "gives the signal" (change of its value from the critical section of "pthread2" (lines 128-167)) to "release" the thread from the loop, i.e., containing the ID value corresponding to the 3rd thread (3). The return value of "pthread_cond_wait ()" is also checked for errors. */
            {
                perror ("pthread_cond_wait () failed to execute");         // Prints an error message to "stderr" for the failure of "pthread_cond_wait ()".
                exit (1);                                                  // The process terminates with "exit value" 1.
            }
        }
        printf ("World! ");                                                // Prints "World! " to "stdout".
        if (cnt_wait > 0)                                                  /* Check if one or more threads are already waiting */
        {
            cnt_signal = 1;                                                // Change the ID value to the one corresponding to the 1st thread (1) (trigger for the next output, the string "What A ").
            if (pthread_cond_broadcast (&cond_var) < 0)                    /* Call to the "pthread_cond_broadcast ()" function from the "POSIX Threads" library (lines 10-11), waking all threads waiting for a signal, ensured by the check in line 191. The return value of "pthread_cond_broadcast ()" is also checked for errors. */
            {
                perror ("pthread_cond_broadcast () failed to execute");    // Prints an error message to "stderr" for the failure of "pthread_cond_broadcast ()".
                exit (1);                                                  // The process terminates with "exit value" 1.
            }
            cnt_wait = 0;                                                  // Reset the count of threads in wait, since the call to "pthread_cond_broadcast ()" in line 194 has already occurred.
        }
        else                                                               /* No threads are in wait */
            cnt_signal = 1;                                                // Since no threads are in wait, simply change the ID value to the one corresponding to the 1st thread (1) (trigger for the next output, the string "What A ").
/***********************************************************************************************************************************************************************************************/
        if (pthread_mutex_unlock (&mut) < 0)                               /* Call to the "pthread_mutex_unlock ()" function from the "POSIX Threads" library (lines 10-11), to unlock the "mutex" (lines 181-202) which was created to protect shared resources in the critical section from simultaneous use by two or more threads, and check for an error return value. */
        {
            perror ("pthread_mutex_unlock () failed to execute");          // Prints an error message to "stderr" for the failure of "pthread_mutex_unlock ()".
            exit (1);                                                      // The process terminates with "exit value" 1.
        }
    }
    pthread_exit (NULL);                                                   // The thread terminates its operation.
}

/***********************************************************************************************************************************************************************************************/

/*  SAMPLE RUNS
    
    #1 ./condition_vars
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
    
    Due to the infinite loops in the critical sections of the three threads, parts of the code remain unexecuted because the loops will not terminate on their own
    but will only stop if the user manually terminates the program. Specifically, the threads will never terminate (the "pthread_exit()" function, imported from the
    "POSIX Threads" libraries (lines 10-11), is located outside the loops of the three critical sections of the three threads on lines 122, 166, and 210 respectively),
    and as a result, they will not be synchronized for their memory deallocation using the "pthread_join()" function (also imported from the "POSIX Threads" libraries 
    (lines 10-11)) on lines 52, 57, and 62. Furthermore, the "pthread_mutex_t" and "pthread_cond_t" variables, i.e., the "mutex" and the "condition variable" imported 
    from the "POSIX Threads" libraries (lines 10-11), will not be freed from memory. Consequently, the process will run indefinitely, and termination will only occur 
    with necessary user intervention.
*/

