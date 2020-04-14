// producer.C
// Student: Kemper, Michael | Clode, Ryan
// RedID: (Kemper)822 86 7065 | (Clode)820 72 7161
#include <iostream>

using namespace std;

void producer(void * VoidPtr) {
  THREAD_DATA	*DataPtr = (THREAD_DATA *) VoidPtr;

  while (TRUE) { 
    sem_wait(DataPtr->MutexPtr);	/* entry */

    /* critical region */
    *(DataPtr->ValuePtr) = *(DataPtr->ValuePtr) + 1;
    // printf("After %s --> %5d\n", DataPtr->Name, *(DataPtr->ValuePtr));
    // fflush(stdout);
    
    sem_post(DataPtr->MutexPtr);	/* exit */
  }
}