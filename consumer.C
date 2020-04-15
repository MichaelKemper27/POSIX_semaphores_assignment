// consumer.C
// Student: Kemper, Michael | Clode, Ryan
// RedID: (Kemper)822 86 7065 | (Clode)820 72 7161
#include "includes.h"

using namespace std;

void * consumer(void * VoidPtr) {
  THREAD_DATA	*DataPtr = (THREAD_DATA *) VoidPtr;

  while (true) { 
    sem_wait(DataPtr->MutexPtr);	/* entry */

    /* critical region */

    if(*(DataPtr->candyCountConsumed) >= 100){
      sem_post(DataPtr->MutexPtr);
      return NULL;
    }

    if(DataPtr->QueuePtr->size() > 0){
      //this_thread::sleep_for(chrono::milliseconds(*(DataPtr->waitTime)));
      Candy c = DataPtr->QueuePtr->front();
      DataPtr->QueuePtr->pop();

        //if frogbite, decrement frog bite counter
      if(c == 1){ 
        *(DataPtr->frogBiteCount) = *(DataPtr->frogBiteCount) - 1;
        *(DataPtr->totalFrogBites) = *(DataPtr->totalFrogBites) + 1;
      } else {
        *(DataPtr->totalSuckers) = *(DataPtr->totalSuckers) + 1;
      }

      //increment candy count consumed
      *(DataPtr->candyCountConsumed) = *(DataPtr->candyCountConsumed) + 1;

      int numTotal = DataPtr->QueuePtr->size();
      int numOfFrogs = *(DataPtr->frogBiteCount);
      int numOfSuckers = numTotal - numOfFrogs;
      int numProduced = *(DataPtr->candyCountProduced);

      cout << "Belt: " << numOfFrogs << " frogs + " << numOfSuckers << " escargos = " << numTotal;
      cout << ". produced: " << numProduced << "\t" << DataPtr->Name <<  " consumed " << Candies[c] << "." << endl;
      fflush(stdout);
    }
    //*(DataPtr->ValuePtr) = *(DataPtr->ValuePtr) - 1;
    // printf("After %s --> %5d\n", DataPtr->Name, *(DataPtr->ValuePtr));
    // fflush(stdout);

    sem_post(DataPtr->MutexPtr);	/* exit */
    this_thread::sleep_for(chrono::milliseconds(*(DataPtr->waitTime)));
  }
  return NULL;
}