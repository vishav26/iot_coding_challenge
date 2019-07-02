/*
 * wd_task.c
 *
 * Created: 02/07/2019 06:36:38
 *  Author: VishavVishav
 */ 

#include <wd_task.h>
#include <atmel_start.h>

void WdTask(void *p)
{
	(void)p;
	//Check if the watchdog Enable bit is disabled. If not, then disable it
	if(hri_wdt_get_CTRLA_ENABLE_bit(WDT) != false)
	{
		//Check if the Always on bit is disabled. If not, then disable it
		if(hri_wdt_get_CTRLA_ALWAYSON_bit(WDT) !=false)
		{
			hri_wdt_clear_CTRLA_ALWAYSON_bit(WDT);
		}
		
		//Disable the Watchdog
		hri_wdt_clear_CTRLA_ENABLE_bit(WDT);
		
		//Set the value of timeout to 2s
		hri_wdt_write_CONFIG_PER_bf(WDT,0x8);
		//Enable the Watchdog
		hri_wdt_set_CTRLA_ENABLE_bit(WDT);
	}
	
	//Reset the Watchdog Timer every 1.5s
	while(1)
	{
		//Write value 0xA5 to reset the timer
		hri_wdt_write_CLEAR_reg(WDT,0xA5);
		
		//Delay of 1.5 seconds
		os_sleep(1500);
		
	}
	
}