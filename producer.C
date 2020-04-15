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
    if(*(DataPtr->candyCountProduced) >= 100){
      sem_post(DataPtr->MutexPtr);
      return NULL;
    }

    //Check if queue is full
    if(DataPtr->QueuePtr->size() < 10){

      //check if frogbite, belt must have < 3
      if(*(DataPtr->producerType) != FROGBITE || *(DataPtr->frogBiteCount) < 3){
        DataPtr->QueuePtr->push(*(DataPtr->producerType));

        //if frogbite, increment frog bite counter
        if(*(DataPtr->producerType) == FROGBITE){
          *(DataPtr->frogBiteCount) = *(DataPtr->frogBiteCount) + 1;
          *(DataPtr->totalFrogBites) = *(DataPtr->totalFrogBites) + 1;
        } else {
          *(DataPtr->totalSuckers) = *(DataPtr->totalSuckers) + 1;
        }

        //increment candy count produced
        *(DataPtr->candyCountProduced) = *(DataPtr->candyCountProduced) + 1;

        int numTotal = DataPtr->QueuePtr->size();
        int numOfFrogs = *(DataPtr->frogBiteCount);
        int numOfSuckers = numTotal - numOfFrogs;
        int numProduced = *(DataPtr->candyCountProduced);

        cout << "Belt: " << numOfFrogs << " frogs + " << numOfSuckers << " escargos = " << numTotal;
        cout << ". produced: " << numProduced << "\t" << "Added " << Candies[*(DataPtr->producerType)] << endl;
        fflush(stdout);
      }
    }
    //*(DataPtr->ValuePtr) = *(DataPtr->ValuePtr) + 1;
    // printf("After %s --> %5d\n", DataPtr->Name, *(DataPtr->ValuePtr));
    // fflush(stdout);
    sem_post(DataPtr->MutexPtr);	/* exit */
    this_thread::sleep_for(chrono::milliseconds(*(DataPtr->waitTime)));
  }
  return NULL;
}