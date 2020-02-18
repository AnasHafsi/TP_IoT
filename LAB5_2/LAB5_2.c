

#include "contiki.h"
#include "net/rime.h"
#include "dev/cc2420.h"
#include "random.h"

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

    static uint8_t txpower;
    static uint8_t i;
    static uint8_t raw_rssi;
    static uint8_t lqi;
    char msg[10];
    broadcast_open(&broadcast, 129, &broadcast_call);

    while (1)
    {
        
        for (i = 32; i > 0; i--)
        {

            etimer_set(&et, CLOCK_SECOND);
            PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
            txpower=i;
            
            raw_rssi=packetbuf_attr(PACKETBUF_ATTR_RSSI);
            lqi=packetbuf_attr(PACKETBUF_ATTR_LINK_QUALITY);
            cc2420_set_txpower(txpower && 0xff);
            packetbuf_set_attr(PACKETBUF_ATTR_RADIO_TXPOWER,txpower);
            sprintf(msg,"Hello %d",txpower);
            packetbuf_copyfrom(msg,sizeof(msg));
            broadcast_send(&broadcast);
            printf("broadcast message sent : %s\nRssi : %d, LQI : %d",msg,raw_rssi,lqi);
            
            
        }
    }

    PROCESS_END();
}
/*---------------------------------------------------------------------------*/
