#ifndef _UART_H
#define _UART_H

#include "s5pv210.h"

void uart_init(void);
void put(char word);
char get(void);
#endif
