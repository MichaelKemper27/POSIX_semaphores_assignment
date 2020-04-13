// consumer.C
// Student: Kemper, Michael | Clode, Ryan
// RedID: (Kemper)822 86 7065 | (Clode)820 72 7161
#include <iostream>

using namespace std;

void consumer(void)
{
  int item;
  while (TRUE) { /* repeat forever */
    if (count == 0) {
      sleep( ); /* if buffer is empty, got to sleep */
    }
    item = remove item( ); /* take item out of buffer */
    count = count − 1; /* decrement count of items in buffer */
    if (count == N − 1)  {
      wakeup(producer); /* was buffer full? */
    }
  consume item(item); /* pr int item */
  }
}