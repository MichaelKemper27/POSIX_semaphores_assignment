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

  WAIT_TIMES waitTimes = parseArguments(argc, argv);

  THREAD_DATA sucker;
  sucker.MutexPtr = &Mutex;
  sucker.QueuePtr = &q;
  sucker.producerType = &s;
  cout << "sucker wait time :" << waitTimes.suckerWait << endl;
  sucker.waitTime = &(waitTimes.suckerWait);

  THREAD_DATA frog;
  frog.MutexPtr = &Mutex;
  frog.QueuePtr = &q;
  frog.producerType = &f;
  frog.waitTime = &(waitTimes.frogBiteWait);

  THREAD_DATA lucy;
  lucy.MutexPtr = &Mutex;
  lucy.QueuePtr = &q;
  lucy.Name = strdup("Lucy");
  lucy.waitTime = &(waitTimes.lucyWait);

  THREAD_DATA ethel;
  ethel.MutexPtr = &Mutex;
  ethel.QueuePtr = &q;
  ethel.Name = strdup("Ethel");
  ethel.waitTime = &(waitTimes.ethelWait);

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

  return 0;
}