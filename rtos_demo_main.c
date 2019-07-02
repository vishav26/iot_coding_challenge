/**
 * \file
 *
 * \brief Application implement
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "atmel_start.h"
#include "atmel_start_pins.h"

#include "hal_io.h"
#include "hal_rtos.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define TASK_CLI_STACK_SIZE (256 / sizeof(portSTACK_TYPE))
#define TASK_WD_STACK_SIZE (256 / sizeof(portSTACK_TYPE))

#define TASK_CLI_PRIORITY (tskIDLE_PRIORITY + 1)
#define TASK_WD_PRIORITY (tskIDLE_PRIORITY + 2)

static TaskHandle_t      xCreatedConsoleTask;
static TaskHandle_t      xCreatedWdTask;


/**
 * \brief Write string to console
 */
static void str_write(const char *s)
{
	io_write(&USART_0.io, (const uint8_t *)s, strlen(s));
}

/**
 * OS task that prints Hello Dott every 1 second
 */
static void task_console(void *p)
{

	(void)p;
	for(;;)
	{
		char *str = "Hello Dott!!\n"; 
		str_write(str);
		vTaskDelay(1000);
	}
		
	
}

static void task_wd(void *p)
{
	(void)p;

	
	//Check if the watchdog Enable bit is disabled. If not, then disable it
	if(hri_wdt_get_CTRLA_ENABLE_bit(WDT) != false)
	{
		//Disable the Watchdog
		hri_wdt_clear_CTRLA_ENABLE_bit(WDT);
	}
	
	//Check if the Always on bit is disabled. If not, then disable it
	if(hri_wdt_get_CTRLA_ALWAYSON_bit(WDT) !=false)
	{
		hri_wdt_clear_CTRLA_ALWAYSON_bit(WDT);
	}
	

	//Set the value of timeout to 2s
	hri_wdt_write_CONFIG_PER_bf(WDT,0x8);
	

	//Enable the Watchdog
	hri_wdt_set_CTRLA_ENABLE_bit(WDT);

	os_sleep(100);

		
	while(1)
	{
		//Write value 0xA5 to reset the timer
		hri_wdt_write_CLEAR_reg(WDT,0xA5);
		
		//Delay of 1.5 seconds

		vTaskDelay(1500);
	}

	
}
/**
 * \brief Create OS task for console output
 */
static void task_console_create(void)
{
	/* Create the task that handles the CLI. */
	if (xTaskCreate(task_console, "Console", TASK_CLI_STACK_SIZE, NULL, TASK_CLI_PRIORITY, &xCreatedConsoleTask)
	    != pdPASS) {
		while (1) {
			;
		}
	}
}

/**
* \brief Create OS task for watchdog
*/
static void task_wd_create(void)
{
	/* Create the task that handles the CLI. */
	if (xTaskCreate(task_wd, "WatchDog", TASK_WD_STACK_SIZE, NULL, TASK_WD_PRIORITY, &xCreatedWdTask)
		!= pdPASS) {
		while (1) {
				;
		}
	}
	
}

int main(void)
{
	atmel_start_init();
	task_console_create();
	task_wd_create();
	vTaskStartScheduler();
	
	return 0;
}


