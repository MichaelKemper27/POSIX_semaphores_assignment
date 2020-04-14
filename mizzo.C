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

void parseArguments(int argc, char **argv) {
  int option;
  int flagCount = 0;
  entryCountSizes = new int[argc];
  while ( (option = getopt(argc, argv, "n:p:t")) != -1) {
    switch (option) {
      case 'E': /* Ethel candy boxing time */
      numMemoryRefs = atoi(optarg);
      flagCount++;
      // optarg will contain the string following -n
      // Process appropriately (e.g. convert to integer atoi(optarg))
      break;
      case 'L': /* Lucy candy boxing time */
      // optarg contains name of page file…
      outputFileName = optarg;
      flagCount++;
      break;
      case 'f': /* Frog bite time */
      // No argument this time, just set a flag
      showLogToPhysTranslation = true;
      break;
      case 'e': /* everlasting escargot sucker time */
      // No argument this time, just set a flag
      showLogToPhysTranslation = true;
      break;
      default:
      // print something about the usage and die…
      break;
    }
 //idx = optind;
  }
  
  int flagTotalCounter = flagCount*2 + (int)showLogToPhysTranslation;

  if(argc > 1) {
    for(int i = flagTotalCounter+1; i < argc; i++) {
      if (isdigit(argv[i][0])) {
        int argAsInt = atoi(argv[i]);
        entryCountSizes[entryCountIndex] = argAsInt;
        entryCountIndex++;
      } else if(sizeof(argv[i]) > 2 && isalpha(argv[i][0])) {
        inputTraceFileName = argv[i];
      }
    }
  }
}

// int main(int argc, char **argv){
//   parseArguments(argc, argv);
// }


void * producer(void * VoidPtr);
void * consumer(void * VoidPtr);

int main(int argc, char **argv) { 
  cout << "Debug: 1" << endl;
  THREAD_DATA belt;
  pthread_t producerThread;
  pthread_t consumerThread;
  cout << "Debug: 2" << endl;
  sem_t Mutex;
  int Value = 0;
  void *ThreadResultPtr;

  belt.MutexPtr = &Mutex;
  belt.ValuePtr = &Value;
  cout << "Debug: 3" << endl;
  //create sem
  if (sem_init(&Mutex, 0, 1) == -1) {
    fprintf(stderr, "Unable to initialize Mutex semaphore\n");
    exit(EXT_SEMAPHORE); //exit codes
  }
  cout << "Debug: 4" << endl;
  //start threads here
  if (pthread_create(&producerThread, NULL, producer, &belt)) {
    fprintf(stderr, "Unable to create producer thread\n");
    exit(EXT_THREAD); //exit codes
  }
  cout << "Debug: 5" << endl;

  if (pthread_join(producerThread, &ThreadResultPtr)) {
    fprintf(stderr, "Thread join error\n");
    exit(EXT_THREAD); //exit codes
  }
  cout << "Debug: 6" << endl;

  return 0;
}