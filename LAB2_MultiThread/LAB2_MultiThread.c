#include "contiki.h"
#include "dev/leds.h"
#include <stdio.h>

PROCESS(GREEN, "GREEN");
PROCESS(RED, "RED");
PROCESS(BLUE, "BLUE");
AUTOSTART_PROCESSES(&GREEN, &RED, &BLUE);

PROCESS_THREAD(GREEN, ev, data)
{
    static struct etimer et;
    PROCESS_BEGIN();
    leds_off(LEDS_GREEN);
    while (1)
    {
        etimer_set(&et, CLOCK_SECOND / 2);
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
        leds_toggle(LEDS_GREEN);
    }
    PROCESS_END();
}
PROCESS_THREAD(RED, ev, data)
{
    static struct etimer et1;
    PROCESS_BEGIN();
    leds_off(LEDS_RED);
    while (1)
    {
        etimer_set(&et1, CLOCK_SECOND);
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et1));
        leds_toggle(LEDS_RED);
    }
    PROCESS_END();
}
PROCESS_THREAD(BLUE, ev, data)
{
    static struct etimer et2;
    PROCESS_BEGIN();
    leds_off(LEDS_BLUE);
    while (1)
    {
        etimer_set(&et2, CLOCK_SECOND / 4);
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et2));
        leds_toggle(LEDS_BLUE);
    }
    PROCESS_END();
}
