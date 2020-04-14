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
  pthread_t producerThread;
  pthread_t consumerThread;
  sem_t Mutex;
  int Value = 0;
  void *ThreadResultPtr;
  queue <Candy> q;


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