#include <stdio.h>
#include "contiki.h"
#include "dev/i2cmaster.h"
#include "dev/tmp102.h"

#define INTERVALE (CLOCK_SECOND / 2)

PROCESS(Temperature, "Calcule de la temperature");
AUTOSTART_PROCESSES(&Temperature);

static struct etimer et;

PROCESS_THREAD(Temperature, ev, data)
{
  PROCESS_BEGIN();

  int16_t tempint, raw, sign;
  uint16_t tempfrac, absraw;
  char minus = ' ';

  tmp102_init();

  while (1)
  {
    etimer_set(&et, INTERVALE);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

    sign = 1;
    raw = tmp102_read_temp_raw();
    absraw = raw;
    if (raw < 0)
    {
      absraw = (raw ^ 0xFFFF) + 1;
      sign = -1;
    }
    tempint = (absraw >> 8) * sign;
    tempfrac = ((absraw >> 4) % 16) * 625;
    minus = ((tempint == 0) & (sign == -1)) ? '-' : ' ';
    PRINTF("Temperature: %c%d.%04d\n", minus, tempint, tempfrac);
  }
  PROCESS_END();
}
