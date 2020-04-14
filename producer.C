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
      DataPtr->QueuePtr->push(SUCKER);
      cout << "Belt: " << "Added " << Candies[0] << endl;
    }
    //*(DataPtr->ValuePtr) = *(DataPtr->ValuePtr) + 1;
    // printf("After %s --> %5d\n", DataPtr->Name, *(DataPtr->ValuePtr));
    // fflush(stdout);
    sem_post(DataPtr->MutexPtr);	/* exit */
  }
}