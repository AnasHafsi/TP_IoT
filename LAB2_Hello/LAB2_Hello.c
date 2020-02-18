#include "contiki.h"
#include <stdio.h>

PROCESS(LAB2_Hello, "Hello");
AUTOSTART_PROCESSES(&LAB2_Hello);
//print hello World every 1 s

PROCESS_THREAD(LAB2_Hello, ev, data)
{
    static struct etimer et;
    PROCESS_BEGIN();

    while (1)
    {
        etimer_set(&et, CLOCK_SECOND);
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
        printf("Hello World\n");
    }
    PROCESS_END();
}
