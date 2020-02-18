

#include <stdio.h>
#include "contiki.h"
#include "dev/adxl345.h"

#define Intervale_de_Lecture CLOCK_SECOND

PROCESS(Accelerometre, "Test de l'accelerometre");
AUTOSTART_PROCESSES(&Accelerometre);

static struct etimer et;

PROCESS_THREAD(Accelerometre, ev, data)
{
  PROCESS_BEGIN();
  {
    int16_t x, y, z;
    accm_init();
    while (1)
    {
      x = accm_read_axis(X_AXIS);
      y = accm_read_axis(Y_AXIS);
      z = accm_read_axis(Z_AXIS);
      printf("x: %d y: %d z: %d\n", x, y, z);

      etimer_set(&et, Intervale_de_Lecture);
      PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
    }
  }
  PROCESS_END();
}
