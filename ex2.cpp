/*
	ex2.cpp
	CSC716 Project
	Created By Yu Tian on 12/10/15
*/
#include <iostream>
#include <cstdlib>
#include <thread>
#include <mutex>
//#include <vector>
#define numReaders 9
#define numWriters 3

using namespace std;

mutex inlock, outlock;
int counter = 0;

void reader(int x) {
    inlock.lock();
    // start critical region

    cout << "Reader Thread " << x << " in critical region...\n";
    cout << "Reader Thread " << x << " is reading files...\n";
    cout << "Reader Thread " << x << " exiting critical region...\n";
    
    // end critical region
    inlock.unlock();
}

void writer(int x) {
    inlock.lock();
    // start critical region
    cout << "Writer Thread " << x << " in critical region...\n";
    cout << "Writer Thread " << x << " is writing files...\n";
    cout << "Writer Thread " << x << " exiting critical region...\n";

    // end critical region
    inlock.unlock();
}

/*
void *wait(void *t)
{
   int i;
   long tid;

   tid = (long)t;

   sleep(1);
   cout << "Sleeping in thread " << endl;
   cout << "Thread with id : " << tid << "  ...exiting " << endl;
   pthread_exit(NULL);
}
*/

int main ()
{
    std::thread threads[numReaders + numWriters];
    int i = 0;
    for (i = 0; i < numReaders; i++) {
        threads[i] = std::thread(reader, i + 1);
    }
    for (i = numReaders; i < numReaders + numWriters; i++) {
        threads[i] = std::thread(writer, i - numReaders + 1);
    }

/*    std::vector<std::thread> threads;
    for (int i=1; i<=7; ++i) threads.push_back(std::thread(reader,i));
    for (int i=1; i<=3; ++i) threads.push_back(std::thread(writer,i));
*/  
    for (auto& th : threads) th.join();

    return 0;


/*
   int rc;
   int i;
   pthread_t threads[NUM_THREADS];
   pthread_attr_t attr;
   void *status;

   // Initialize and set thread joinable
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

   for( i=0; i < NUM_THREADS; i++ ){
      cout << "main() : creating thread, " << i << endl;
      rc = pthread_create(&threads[i], NULL, wait, (void *)i );
      if (rc){
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
   }


   // free attribute and wait for the other threads
   pthread_attr_destroy(&attr);
   for( i=0; i < NUM_THREADS; i++ ){
      rc = pthread_join(threads[i], &status);
      if (rc){
         cout << "Error:unable to join," << rc << endl;
         exit(-1);
      }
      cout << "Main: completed thread id :" << i ;
      cout << "  exiting with status :" << status << endl;
   }

   cout << "Main: program exiting." << endl;
   pthread_exit(NULL);
*/
}


