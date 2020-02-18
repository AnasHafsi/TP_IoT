

#include "contiki.h"
#include "net/rime.h"
#include "random.h"
#include "dev/i2cmaster.h"
#include "dev/tmp102.h"

#include "dev/button-sensor.h"

#include "dev/leds.h"

#include <stdio.h>
/*---------------------------------------------------------------------------*/
PROCESS(example_broadcast_process, "Broadcast example");
AUTOSTART_PROCESSES(&example_broadcast_process);
/*---------------------------------------------------------------------------*/
static void
broadcast_recv(struct broadcast_conn *c, const rimeaddr_t *from)
{
  printf("broadcast message received from %d.%d: '%s'\n",
         from->u8[0], from->u8[1], (char *)packetbuf_dataptr());
}
static const struct broadcast_callbacks broadcast_call = {broadcast_recv};
static struct broadcast_conn broadcast;
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(example_broadcast_process, ev, data)
{
  static struct etimer et;

  PROCESS_EXITHANDLER(broadcast_close(&broadcast);)

  PROCESS_BEGIN();
  int16_t tempint;
  uint16_t tempfrac;
  int16_t raw;
  uint16_t absraw;
  int16_t sign;
  char minus = ' ';

  tmp102_init();


  broadcast_open(&broadcast, 129, &broadcast_call);

  while(1) {
    sign = 1;
    /* Delay 2-4 seconds */
    etimer_set(&et, CLOCK_SECOND * 4 + random_rand() % (CLOCK_SECOND * 4));
    
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
    ////////////////////////////////////////////////////
    raw = tmp102_read_temp_raw();
    absraw = raw;
    if(raw < 0) {		// Perform 2C's if sensor returned negative data
      absraw = (raw ^ 0xFFFF) + 1;
      sign = -1;
    }
    tempint = (absraw >> 8) * sign;
    tempfrac = ((absraw >> 4) % 16) * 625;	// Info in 1/10000 of degree
    minus = ((tempint == 0) & (sign == -1)) ? '-' : ' ';

    //////////////////////////////////////////
    char i[50]="";
    int n=sprintf (i, "Anas is sending Temp : %c%d.%04d", minus, tempint, tempfrac);
    int raw_rssi=packetbuf_attr(PACKETBUF_ATTR_RSSI);
    int lqi=packetbuf_attr(PACKETBUF_ATTR_LINK_QUALITY);
    printf(" \nrssi : %d lqi %d\n",raw_rssi,lqi);
    packetbuf_copyfrom(i, n);
    broadcast_send(&broadcast);
    printf("broadcast message sent\n");
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
