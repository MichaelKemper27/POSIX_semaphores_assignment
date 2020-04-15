// includes.h
// Student: Kemper, Michael | Clode, Ryan
// RedID: (Kemper)822 86 7065 | (Clode)820 72 7161
#ifndef INCLUDES_H
#define INCLUDES_H

#include <iostream>
#include <fstream>
#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <queue>
#include <thread>
#include <chrono>
#include <string.h>

using namespace std;

enum Candy {
  SUCKER,
  FROGBITE
};

static const char * Candies[] = { "escargo sucker", "frog bite" };

struct THREAD_DATA {
  char *Name;       
  sem_t *MutexPtr;	/* pointer to critical region semaphore */
  queue<Candy> *QueuePtr;
  int *candyCountProduced;
  int *candyCountConsumed;
  int *frogBiteCount;
  int *waitTime;
  Candy *producerType;
  int totalFrogBitesConsumed;
  int totalSuckersConsumed;
};

#endif