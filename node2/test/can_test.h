#ifndef _CANTEST_H_
#define _CANTEST_H_

#include <stdio.h>
#include <stdarg.h>
#include "sam.h"
#include "drivers/can.h"

#define F_CPU 84000000

void CANTEST_RecieveSend(void);

#endif
