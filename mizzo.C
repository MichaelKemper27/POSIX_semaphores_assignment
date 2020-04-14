// mizzo.C
// Student: Kemper, Michael | Clode, Ryan
// RedID: (Kemper)822 86 7065 | (Clode)820 72 7161
#define EXT_SEMAPHORE 10
#define EXT_THREAD 15
#include "includes.h"

using namespace std;

// char* outputFileName;
// char* inputTraceFileName;
// int* entryCountSizes;
// int entryCountIndex = 0;
// bool showLogToPhysTranslation = false;
// int numMemoryRefs = -1;

// void parseArguments(int argc, char **argv) {
//   int option;
//   int flagCount = 0;
//   entryCountSizes = new int[argc];
//   while ( (option = getopt(argc, argv, "n:p:t")) != -1) {
//     switch (option) {
//       case 'n': /* Number of addresses to process */
//       numMemoryRefs = atoi(optarg);
//       flagCount++;
//       // optarg will contain the string following -n
//       // Process appropriately (e.g. convert to integer atoi(optarg))
//       break;
//       case 'p': /* produce map of pages */
//       // optarg contains name of page file…
//       outputFileName = optarg;
//       flagCount++;
//       break;
//       case 't': /* Show address translation */
//       // No argument this time, just set a flag
//       showLogToPhysTranslation = true;
//       break;
//       default:
//       // print something about the usage and die…
//       break;
//     }
//  //idx = optind;
//   }
  
//   int flagTotalCounter = flagCount*2 + (int)showLogToPhysTranslation;

//   if(argc > 1) {
//     for(int i = flagTotalCounter+1; i < argc; i++) {
//       if (isdigit(argv[i][0])) {
//         int argAsInt = atoi(argv[i]);
//         entryCountSizes[entryCountIndex] = argAsInt;
//         entryCountIndex++;
//       } else if(sizeof(argv[i]) > 2 && isalpha(argv[i][0])) {
//         inputTraceFileName = argv[i];
//       }
//     }
//   }
// }

// int main(int argc, char **argv){
//   parseArguments(argc, argv);
// }


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

  THREAD_DATA sucker;
  sucker.MutexPtr = &Mutex;
  sucker.QueuePtr = &q;
  sucker.producerType = &s;

  THREAD_DATA frog;
  frog.MutexPtr = &Mutex;
  frog.QueuePtr = &q;
  frog.producerType = &f;

  THREAD_DATA lucy;
  lucy.MutexPtr = &Mutex;
  lucy.QueuePtr = &q;
  lucy.Name = strdup("Lucy");

  THREAD_DATA ethel;
  ethel.MutexPtr = &Mutex;
  ethel.QueuePtr = &q;
  ethel.Name = strdup("Ethel");

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