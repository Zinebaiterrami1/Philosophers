#include <stdio.h>
#include <unistd.h>
#include <threads.h>
#include <pthread.h>

// //just a single thread
// void *start_routine(void *arg)
// {
//     printf("Hello from thread\n");
//     return NULL;
// }

// int main(int argc, char **argv)
// {
//     pthread_t thread;
//     int i;

//     i = 1; 
//     // create the thread
//     pthread_create(&thread, NULL, start_routine, NULL);
//     // wait for the thread to finish
//     pthread_join(thread, NULL);
//     //clean up resources , this is unnecessary
//     pthread_detach(thread);
// }

/*-----------------------------now creatin multi threads and print a message in each one----------------*/

// void *start_routine(void *arg)
// {
//     int num_thread;

//     num_thread = *(int *)arg;
//     printf("Hello from thread %d\n", num_thread);
//     return (NULL);
// }

// int main()
// {
//     pthread_t thread[5];
//     int ids[5];
//     int i;

//     i = 0;
//     while(i < 5)
//     {   
//         ids[i] = i + 1;
//         pthread_create(&thread[i], NULL, start_routine, &ids[i]);
//         i++;
//     }
//     i = 0;
//     while(i < 5)
//     {
//         pthread_join(thread[i], NULL);
//         i++;
//     }
// }

/**************practin mutex******************** */

// int main()
// {
//     int counter;
//     pthread_mutex_t mutex;

//     counter = 0;
//     pthread_mutex_init(&mutex, NULL);
//     printf("counter before lock\n");
//     pthread_mutex_lock(&mutex);
//     counter++;
//     pthread_mutex_unlock(&mutex);
//     printf("counter after lock %d\n", counter);
// }

/****combine the two toghether mutex && threads****/

void *start_routine(void *arg)
{
    int counter;
    int i;
    pthread_mutex_t mutex;

    i = 0;
    counter = 1;
    while(i < 10000)
    {
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
        i++;
    }
    printf("Final counter: %d\n", counter);
    return NULL;
}

int main()
{
    pthread_mutex_t mutex;
    pthread_t thread[5];
    pthread_mutex_init(&mutex, NULL);
    int i = 0;
    while(i < 5)
    {
        pthread_create(&thread[i], NULL, start_routine, NULL);
        i++;
    }
    i = 0;
    while(i < 5)
    {
        pthread_join(thread[i], NULL);
        i++;
    }
    pthread_mutex_destroy(&mutex);
}