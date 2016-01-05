/*
	testset.cpp
	CSC716 Project
	Created By Yu Tian on 12/10/15
*/

// atomic_flag as a spinning lock
#include <iostream>       // std::cout
#include <atomic>         // std::atomic_flag
#include <thread>         // std::thread
#include <vector>         // std::vector
#include <sstream>        // std::stringstream
#include <time.h>
#include <unistd.h>

#define numReaders 9
#define numWriters 3

std::atomic_flag mutex = ATOMIC_FLAG_INIT;
std::atomic_flag lock = ATOMIC_FLAG_INIT;
std::stringstream stream;

int counter = 0;
int acReaders = 0;

int getRand() {
    return rand() % 10 + 1;
}

void reader(int x) {
    while (counter < 30) {
        sleep(getRand());
        int st = getRand();
        while (mutex.test_and_set()) {}
        acReaders++;
        if (numReaders == 1) {
            while (lock.test_and_set()) {}
        }
        mutex.clear();
        // start critical region

        counter++;
        std::cout << "Reader Thread " << x << " in critical region...\n";
        std::cout << "active readers: " << acReaders << "\n";
        std::cout << "Now Reader Thread " << x << " sleep " << st << " seconds\n";
        sleep(st);
        std::cout << "Reader Thread " << x << " is reading files...\n";
        std::cout << "Reader Thread " << x << " exiting critical region...\n";
        

    /*
        std::cout << "Reader Thread " << x << " in critical region...\n";
        std::cout << "active readers: " << acReaders << "\n";
        std::cout << "Reader Thread " << x << " is reading files...\n";
        std::cout << "Reader Thread " << x << " exiting critical region...\n";
      */  
        // end critical region
        while (mutex.test_and_set()) {}
        acReaders--;
        if (numReaders == 0) {
            lock.clear();
        }
        mutex.clear();
        sleep(getRand());
    }
}

void writer(int x) {
    while (counter < 30) {
        sleep(getRand());
        int st = getRand();
        while (lock.test_and_set()) {}
        // start critical region

        counter++;
        std::cout << "Writer Thread " << x << " in critical region...\n";
        std::cout << "Now Writer Thread " << x << " sleep " << st << " seconds\n";
        sleep(st);
        std::cout << "Writer Thread " << x << " is writing files...\n";
        std::cout << "Writer Thread " << x << " exiting critical region...\n";
    /*
        std::cout << "Writer Thread " << x << " in critical region...\n";
        std::cout << "Writer Thread " << x << " is writing files...\n";
        std::cout << "Writer Thread " << x << " exiting critical region...\n";
    */
        // end critical region
        lock.clear();
        sleep(getRand());
    }
}

int main ()
{
    std::vector<std::thread> threads;
    for (int i=0; i<numReaders; ++i) threads.push_back(std::thread(reader,i));
    for (int i=0; i<numWriters; ++i) threads.push_back(std::thread(writer,i));
    for (auto& th : threads) th.join();

//    std::cout << stream.str();

    return 0;
}

