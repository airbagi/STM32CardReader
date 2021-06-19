/*
 * systick.c
 *
 */
#include "stm32f4xx.h"
#include "systick.h"

static volatile uint32_t timestamp = 0;
/** Sys-tick timer */
#define SYS_TICK_TIMER                TIM2
#define SYS_TICK_TIMER_PERIPH         RCC_APB1Periph_TIM2
#define SYS_TICK_TIMER_IRQ            TIM2_IRQn
#define SYS_TICK_TIMER_HANDLER        TIM2_IRQHandler
#define SYS_TICK_TIMER_PERIPH_FREQ    84 //MHZ

void sysTickSetup(void)
	{
	/*=================  systick timer =======================*/
	/* Timer enable clock */
	RCC_APB1PeriphClockCmd(SYS_TICK_TIMER_PERIPH, ENABLE);
	TIM_TimeBaseInitTypeDef tim_base;
	TIM_TimeBaseStructInit(&tim_base);
	tim_base.TIM_Prescaler = SYS_TICK_TIMER_PERIPH_FREQ - 1; // 1MHZ
	tim_base.TIM_Period = 0xFFFFFFFF;
	tim_base.TIM_CounterMode = TIM_CounterMode_Up;
	tim_base.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(SYS_TICK_TIMER, &tim_base);
	TIM_SetCounter(SYS_TICK_TIMER, 0);
	TIM_Cmd(SYS_TICK_TIMER, ENABLE); //
	}

void sysTickDisable()
	{
	TIM_Cmd(SYS_TICK_TIMER, DISABLE); //
	}

uint32_t sysTickGet()
	{
	return TIM_GetCounter(SYS_TICK_TIMER);
	}


void sysTickDelay(uint32_t nMSTime)
	{
	uint32_t nFinish = sysTickGet() + nMSTime*1000 - 40;
	while (nFinish > sysTickGet())
		;
	}

