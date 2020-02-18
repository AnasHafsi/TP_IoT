
#include <stdio.h>
#include "contiki.h"
#include "dev/button-sensor.h"
#include "dev/leds.h"
#include "dev/z1-phidgets.h"
PROCESS(Button_proc, "Button Test");
AUTOSTART_PROCESSES(&Button_proc);
PROCESS_THREAD(Button_proc, ev, data)
{
  static struct etimer et;
  PROCESS_BEGIN();
  SENSORS_ACTIVATE(phidgets);
  SENSORS_ACTIVATE(button_sensor);

  while (1)
  {
    etimer_set(&et, CLOCK_SECOND * 2);

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
    leds_toggle(LEDS_GREEN);
    printf("Phidget 5V 1:%d\n", phidgets.value(PHIDGET5V_1));
    printf("Phidget 5V 2:%d\n", phidgets.value(PHIDGET5V_2));
    printf("Phidget 3V 1:%d\n", phidgets.value(PHIDGET3V_1));
    printf("Phidget 3V 2:%d\n", phidgets.value(PHIDGET3V_2));

    if (phidgets.value(PHIDGET3V_1) < 100)
    {
      printf("Button clicked\n");
      leds_on(LEDS_RED);
    }
    else
    {
      leds_off(LEDS_RED);
    }
  }
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
