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

using namespace std;

enum Candy {
  SUCKER,
  FROGBITE
};

struct THREAD_DATA {
  char *Name;       /* Human readable name of operation */
  sem_t *MutexPtr;	/* pointer to critical region semaphore */
  int *ValuePtr;	  /* pointer to shared data */
  queue<Candy> *candyQueue = new queue<Candy>;
  int *candyCount;
  int *frogBiteCount;

};

#endif