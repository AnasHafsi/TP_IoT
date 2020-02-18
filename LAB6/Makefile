all: broadcast-example unicast-sender unicast-receiver
APPS=servreg-hack
CONTIKI=../../contiki

DEFINES=RF_CHANNEL=15

WITH_UIP6=1
UIP_CONF_IPV6=1
CFLAGS+= -DUIP_CONF_IPV6_RPL

include $(CONTIKI)/Makefile.include
