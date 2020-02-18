#include <stdio.h>
#include "contiki.h"
#include "dev/button-sensor.h"
#include "dev/leds.h"
#include "dev/z1-phidgets.h"
PROCESS(Proximity, "Proximity sensor");
AUTOSTART_PROCESSES(&Proximity);

PROCESS_THREAD(Proximity, ev, data)

{
    static struct etimer et, et1;
    SENSORS_ACTIVATE(phidgets);
    PROCESS_BEGIN();

    while (1)
    {
        etimer_set(&et, CLOCK_SECOND / 2);
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

        printf("Phidget 5V 1:%d\n", phidgets.value(PHIDGET5V_1));
        printf("Phidget 3V 1:%d\n", phidgets.value(PHIDGET3V_1));
        leds_off(LEDS_RED);
        leds_off(LEDS_GREEN);
        if (phidgets.value(PHIDGET3V_1) < 25)
        {
            printf("You Are near");
            leds_on(LEDS_GREEN);
        }
        else
        {
            printf("You are Far");
            leds_on(LEDS_RED);
        }
    }
    PROCESS_END();
}
