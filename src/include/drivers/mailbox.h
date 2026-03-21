#ifndef DRIVERS_MAILBOX_H
#define DRIVERS_MAILBOX_H

#include <stdint.h>

int mbox_call(volatile uint32_t *msg);

#endif
