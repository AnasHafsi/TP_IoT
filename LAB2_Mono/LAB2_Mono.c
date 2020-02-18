#include "contiki.h"
#include "dev/leds.h"
#include <stdio.h>

PROCESS(LAB2_Mono, "Blinking Monothread");
AUTOSTART_PROCESSES(&LAB2_Mono);

PROCESS_THREAD(LAB2_Mono, ev, data)
{
	PROCESS_BEGIN();
	leds_off(LEDS_ALL);
	static int16_t ticks = 0;
	static struct etimer et;
	while (1)
	{
		if (ticks == 4)
			ticks = 0;

		etimer_set(&et, CLOCK_SECOND / 4);
		PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
		
		leds_toggle(LEDS_BLUE);

		if (ticks % 2 == 0)
			leds_toggle(LEDS_RED);

		if (ticks % 4 == 0)
			leds_toggle(LEDS_GREEN);

		ticks++;
	}
	PROCESS_END();
}
