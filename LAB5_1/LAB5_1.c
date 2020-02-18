#include "contiki.h"
#include "net/rime.h"
#include "net/netstack.h"
#include "dev/leds.h"
#include "dev/cc2420.h"
#include "dev/cc2420_const.h"
#include "dev/spi.h"
#include <stdio.h>

/*---------------------------------------------------------------------------*/
static void set_frq(int c)
{
  int f;
  // We can read even other channels with CC2420!
  // Fc = 2048 + FSCTRL  ;  Fc = 2405 + 5(k-11) MHz, k=11,12, ... , 26
  f = c + 352; // Start from 2400 MHz to 2485 MHz,
  //FASTSPI_SETREG(CC2420_FSCTRL, f);
  //FASTSPI_STROBE(CC2420_SRXON);
  CC2420_WRITE_REG(CC2420_FSCTRL, f);
  CC2420_STROBE(CC2420_SRXON);
}

static void
do_rssi(void)
{
  int channel;
  printf("RSSI:");
  for(channel = 0; channel <= 85; ++channel) {
    set_frq(channel);
    printf("%d ", cc2420_rssi() + 55);
  }
  printf("\n");
}

/*---------------------------------------------------------------------------*/
PROCESS(scanner_process, "RSSI Scanner");
AUTOSTART_PROCESSES(&scanner_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(scanner_process, ev, data)
{
  PROCESS_BEGIN();
  /* switch mac layer off, and turn radio on */
  NETSTACK_MAC.off(0);
  cc2420_on();

  while(1) {
    do_rssi();
    PROCESS_PAUSE();
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
