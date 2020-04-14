// producer.C
// Student: Kemper, Michael | Clode, Ryan
// RedID: (Kemper)822 86 7065 | (Clode)820 72 7161
#include "includes.h"

using namespace std;

void * producer(void * VoidPtr) {
  THREAD_DATA	*DataPtr = (THREAD_DATA *) VoidPtr;

  while (true) { 
    sem_wait(DataPtr->MutexPtr);	/* entry */

    /* critical region */
    if(DataPtr->QueuePtr->size() < 10){
      this_thread::sleep_for(chrono::milliseconds(*(DataPtr->waitTime)));
      DataPtr->QueuePtr->push(*(DataPtr->producerType));
      cout << "Belt: " << "Added " << Candies[*(DataPtr->producerType)] << endl;
    }
    //*(DataPtr->ValuePtr) = *(DataPtr->ValuePtr) + 1;
    // printf("After %s --> %5d\n", DataPtr->Name, *(DataPtr->ValuePtr));
    // fflush(stdout);
    sem_post(DataPtr->MutexPtr);	/* exit */
  }
}