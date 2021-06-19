#ifndef __SYSTICKH
#define __SYSTICKH

void sysTickSetup();
void sysTickDelay(uint32_t nTime);
uint32_t sysTickGet();
void sysTickDisable();

#endif
