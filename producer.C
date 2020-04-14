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
    *(DataPtr->ValuePtr) = *(DataPtr->ValuePtr) + 1;
    // printf("After %s --> %5d\n", DataPtr->Name, *(DataPtr->ValuePtr));
    // fflush(stdout);
    cout << "incremented valuePtr in producer -> " << *(DataPtr->ValuePtr) << endl;
    sem_post(DataPtr->MutexPtr);	/* exit */
  }
}