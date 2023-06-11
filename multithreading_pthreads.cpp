#include <iostream>
#include <pthread.h>

using namespace std;

#define THREAD_COUNT 7

// There are various ways to use multithreading in C++, we can either use regular threads
// from the thread header or we can use the p_threads. This code will be using P threads
// We will be generating 7 process on 7 different threads and running them at the same time
// Threads are much more efficient than cores and also cause the processes to run in an optimised manner

struct Thread {
    int thread_id;
    string message;
};

void *printMessage(void *threadargs) {
   struct Thread *my_data;
   my_data = (struct Thread *) threadargs;

   cout << "Thread ID : " << my_data->thread_id ;
   cout << " Message : " << my_data->message << endl;

   pthread_exit(NULL);
}

int main () {
   pthread_t threads[THREAD_COUNT];
   struct Thread td[THREAD_COUNT];
   int return_code;
   int i;

   for( i = 0; i < THREAD_COUNT; i++ ) {
      cout <<"main() : creating thread, thread number -> " << i << endl;
      td[i].thread_id = i;
      td[i].message = "This could be any message";
      return_code = pthread_create(&threads[i], NULL, printMessage, (void *)&td[i]);
      
      if (return_code) {
         cout << "Error:unable to create thread," << return_code << endl;
         exit(-1);
      }
   }
   pthread_exit(NULL);
}

