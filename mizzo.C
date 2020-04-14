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
}

WAIT_TIMES parseArguments(int argc, char **argv) {
  int option;
  WAIT_TIMES waitTimes;
  waitTimes.ethelWait = 0;
  waitTimes.lucyWait = 0;
  waitTimes.frogBiteWait = 0;
  waitTimes.suckerWait = 0;
  entryCountSizes = new int[argc];
  while ( (option = getopt(argc, argv, "n:p:t")) != -1) {
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
  pthread_t producerThread;
  pthread_t consumerThread;
  sem_t Mutex;
  int Value = 0;
  void *ThreadResultPtr;
  queue <Candy> q;

  WAIT_TIMES waitTimes = parseArguments(argc, argv);

  THREAD_DATA belt;
  belt.MutexPtr = &Mutex;
  belt.ValuePtr = &Value;
  belt.QueuePtr = &q;

  THREAD_DATA lucy;
  //char *lucyName = "lucy";
  lucy.MutexPtr = &Mutex;
  lucy.ValuePtr = &Value;
  lucy.QueuePtr = &q;
  lucy.Name = strdup("Lucy");

  THREAD_DATA ethel;
  ethel.MutexPtr = &Mutex;
  ethel.ValuePtr = &Value;
  ethel.QueuePtr = &q;
  ethel.Name = strdup("Ethel");

  //create sem
  if (sem_init(&Mutex, 0, 1) == -1) {
    fprintf(stderr, "Unable to initialize Mutex semaphore\n");
    exit(EXT_SEMAPHORE); //exit codes
  }

  //start threads here
  if (pthread_create(&producerThread, NULL, producer, &belt)) {
    fprintf(stderr, "Unable to create producer thread\n");
    exit(EXT_THREAD); //exit codes
  }
  if (pthread_create(&consumerThread, NULL, consumer, &lucy)) {
    fprintf(stderr, "Unable to create consumer thread\n");
    exit(EXT_THREAD); //exit codes
  }
  


  if (pthread_join(producerThread, &ThreadResultPtr)) {
    fprintf(stderr, "Thread join error\n");
    exit(EXT_THREAD); //exit codes
  }
  if (pthread_join(consumerThread, &ThreadResultPtr)) {
    fprintf(stderr, "Thread join error\n");
    exit(EXT_THREAD); //exit codes
  }
  cout << "Debug: 6" << endl;

  return 0;
}