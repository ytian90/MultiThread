/*
	monitor.cpp
	CSC716 Project
	Created By Yu Tian on 12/10/15
*/

#include <iostream>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <vector>
#include <time.h>
#include <unistd.h>
#define numReaders 9
#define numWriters 3

using namespace std;

mutex inlock, outlock;
int counter = 0;
int acReaders = 0;

int getRand() {
    int res;
    res = rand() % 10 + 1;
    return res;
}

void reader(int x) {
    while (counter < 30) {
        sleep(getRand());
        int st = getRand();
        outlock.lock();
        acReaders++;
        if (acReaders == 1) {
            inlock.lock();
        }
        outlock.unlock();
        // start critical region

        counter++;
        cout << "Reader Thread " << x << " in critical region...\n";
        cout << "active readers: " << acReaders << "\n";
        cout << "Now Reader Thread " << x << " sleep " << st << " seconds\n";
        sleep(st);
        cout << "Reader Thread " << x << " is reading files...\n";
        cout << "Reader Thread " << x << " exiting critical region...\n";
        
        // end critical region
        outlock.lock();
        acReaders--;
        if (acReaders == 0) {
            inlock.unlock();
        }
        outlock.unlock();
        sleep(getRand());

    }
}

void writer(int x) {
    while (counter < 30) {
        sleep(getRand());
        int st = getRand();
        inlock.lock();
        // start critical region
        counter++;
        cout << "Writer Thread " << x << " in critical region...\n";
        cout << "Now Writer Thread " << x << " sleep " << st << " seconds\n";
        sleep(st);
        cout << "Writer Thread " << x << " is writing files...\n";
        cout << "Writer Thread " << x << " exiting critical region...\n";

        // end critical region
        inlock.unlock();
        sleep(getRand());

    }
}


int main ()
{
    std::vector<std::thread> threads;
    for (int i=0; i<numReaders; ++i) threads.push_back(std::thread(reader,i));
    for (int i=0; i<numWriters; ++i) threads.push_back(std::thread(writer,i));
  
    for (auto& th : threads) th.join();
/*
    for (int i = 0; i < 10; i++) {
        int temp = getRand();
        std::cout << temp << "\n";
    }
*/
    return 0;


}


