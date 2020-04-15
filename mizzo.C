// mizzo.C
// Student: Kemper, Michael | Clode, Ryan
// RedID: (Kemper)822 86 7065 | (Clode)820 72 7161
#define EXT_SEMAPHORE 10
#define EXT_THREAD 15
#include "includes.h"

using namespace std;

struct WAIT_TIMES {
  int ethelWait;
  int lucyWait;
  int frogBiteWait;
  int suckerWait;
};

WAIT_TIMES parseArguments(int argc, char **argv) {
  int option;
  struct WAIT_TIMES waitTimes = {0, 0, 0, 0};
  while ( (option = getopt(argc, argv, ":e:L:f:E:")) != -1) {
    switch (option) {
      case 'E': /* Ethel candy boxing time */
      waitTimes.ethelWait = atoi(optarg);
      // Process appropriately (e.g. convert to integer atoi(optarg))
      break;
      case 'L': /* Lucy candy boxing time */
      waitTimes.lucyWait = atoi(optarg);
      // Process appropriately (e.g. convert to integer atoi(optarg))
      break;
      case 'f': /* Frog bite time */
      waitTimes.frogBiteWait = atoi(optarg);
      // Process appropriately (e.g. convert to integer atoi(optarg))
      break;
      case 'e': /* everlasting escargot sucker time */
      waitTimes.suckerWait = atoi(optarg);
      // Process appropriately (e.g. convert to integer atoi(optarg))
      break;
      default:
      // print something about the usage and die…
      break;
    }
  }

  return waitTimes;
}

void * producer(void * VoidPtr);
void * consumer(void * VoidPtr);

int main(int argc, char **argv) { 
  pthread_t producerThreadS;
  pthread_t producerThreadF;
  pthread_t consumerThreadL;
  pthread_t consumerThreadE;
  sem_t Mutex;
  void *ThreadResultPtr;
  queue <Candy> q;
  Candy s = SUCKER;
  Candy f = FROGBITE;
  int frogBiteCount = 0;
  int candyCountProduced = 0;
  int candyCountConsumed = 0;


  WAIT_TIMES waitTimes = parseArguments(argc, argv);

  THREAD_DATA sucker = {
    NULL, 
    &Mutex, 
    &q, 
    &candyCountProduced, 
    &candyCountConsumed,
    &frogBiteCount, 
    &(waitTimes.suckerWait), 
    &s, 
    0, 
    0
  };
  
  THREAD_DATA frog = {
    NULL, 
    &Mutex, 
    &q, 
    &candyCountProduced, 
    &candyCountConsumed, 
    &frogBiteCount, 
    &(waitTimes.frogBiteWait), 
    &f, 
    0, 
    0
  };

  THREAD_DATA lucy = {
    strdup("Lucy"), 
    &Mutex, 
    &q, 
    &candyCountProduced, 
    &candyCountConsumed, 
    &frogBiteCount, 
    &(waitTimes.lucyWait), 
    NULL, 
    0, 
    0
  };

  THREAD_DATA ethel = {
    strdup("Ethel"), 
    &Mutex, 
    &q, 
    &candyCountProduced, 
    &candyCountConsumed, 
    &frogBiteCount, 
    &(waitTimes.ethelWait), 
    NULL, 
    0, 
    0
  };


  //create sem
  if (sem_init(&Mutex, 0, 1) == -1) {
    fprintf(stderr, "Unable to initialize Mutex semaphore\n");
    exit(EXT_SEMAPHORE); //exit codes
  }

  //start threads here
  if (pthread_create(&producerThreadS, NULL, producer, &sucker)) {
    fprintf(stderr, "Unable to create producer thread\n");
    exit(EXT_THREAD); //exit codes
  }
  if (pthread_create(&producerThreadF, NULL, producer, &frog)) {
    fprintf(stderr, "Unable to create producer thread\n");
    exit(EXT_THREAD); //exit codes
  }
  if (pthread_create(&consumerThreadL, NULL, consumer, &lucy)) {
    fprintf(stderr, "Unable to create consumer thread\n");
    exit(EXT_THREAD); //exit codes
  }
  if (pthread_create(&consumerThreadE, NULL, consumer, &ethel)) {
    fprintf(stderr, "Unable to create consumer thread\n");
    exit(EXT_THREAD); //exit codes
  }

  if (pthread_join(producerThreadS, &ThreadResultPtr)) {
    fprintf(stderr, "Thread join error\n");
    exit(EXT_THREAD); //exit codes
  }
  if (pthread_join(producerThreadF, &ThreadResultPtr)) {
    fprintf(stderr, "Thread join error\n");
    exit(EXT_THREAD); //exit codes
  }
  if (pthread_join(consumerThreadL, &ThreadResultPtr)) {
    fprintf(stderr, "Thread join error\n");
    exit(EXT_THREAD); //exit codes
  }
  if (pthread_join(consumerThreadE, &ThreadResultPtr)) {
    fprintf(stderr, "Thread join error\n");
    exit(EXT_THREAD); //exit codes
  }


  cout << "\nPRODUCTION REPORT" << endl;
  cout << "----------------------------------------" << endl;

  int totalFrogBites = lucy.totalFrogBitesConsumed + ethel.totalFrogBitesConsumed;
  int totalSuckers = lucy.totalSuckersConsumed + ethel.totalSuckersConsumed;

  cout << "crunchy frog bite producer generated " << totalFrogBites << " candies" << endl;
  cout << "escargot sucker producer generated " << totalSuckers << " candies" << endl;
  cout << "Lucy consumed " << lucy.totalFrogBitesConsumed << " crunchy frog bites + " << lucy.totalSuckersConsumed << " escargot suckers = " << lucy.totalSuckersConsumed + lucy.totalFrogBitesConsumed << endl;
  cout << "Ethel consumed " << ethel.totalFrogBitesConsumed << " crunchy frog bites + " << ethel.totalSuckersConsumed << " escargot suckers = " << ethel.totalSuckersConsumed + ethel.totalFrogBitesConsumed << endl;


  return 0;
}