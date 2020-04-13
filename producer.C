// producer.C
// Student: Kemper, Michael | Clode, Ryan
// RedID: (Kemper)822 86 7065 | (Clode)820 72 7161
#include <iostream>

using namespace std;

void producer(void)
{
  int item;
  while (TRUE) { /* repeat forever */
    item = produce item( ); /* generate next item */
    if (count == N) {
      sleep( ); /* if buffer is full, go to sleep */
    }
    insert item(item); /* put item in buffer */
    count = count + 1; /* increment count of items in buffer */
    if (count == 1) {
      wakeup(consumer); /* was buffer empty? */
    }
  }
}