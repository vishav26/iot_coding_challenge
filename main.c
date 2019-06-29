#include <atmel_start.h>

#define TASK_HELLO_STACK_SIZE (108 / sizeof(portSTACK_TYPE))
#define TASK_HELLO_STACK_PRIORITY (tskIDLE_PRIORITY + 1)

#define TASK_WD_STACK_SIZE (108 / sizeof(portSTACK_TYPE))
#define TASK_WD_STACK_PRIORITY (tskIDLE_PRIORITY + 2)

static TaskHandle_t xCreatedHelloTask;
static TaskHandle_t xCreatedWdTask;

static void helloTask(void *p)
{
	(void)p;
	struct io_descriptor *io;
	//Map the io descriptor to USART
	usart_sync_get_io_descriptor(&USART_0, &io);
	
	//Enable the USART
	usart_sync_enable(&USART_0);
	
	for(;;)
	{
		//Send the message to UART port
		io_write(io, (uint8_t *)"Hello Dott!!", 12);
		//Delay of 1s
		os_sleep(1000);
	}
	
}

static void WdTask(void *p)
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

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	/* Create task to print Hello Dott */
	if (xTaskCreate(helloTask, "Hello", TASK_HELLO_STACK_SIZE, NULL, TASK_HELLO_STACK_PRIORITY, &xCreatedHelloTask) != pdPASS) {
		while (1) {
			;
		}
	}
	
	/*Create Task for Watchdog Timer*/
	if(xTaskCreate(WdTask,"Watchdog", TASK_WD_STACK_SIZE, NULL, TASK_WD_STACK_PRIORITY,&xCreatedWdTask)!= pdPASS)
	{
		while(1){
			;
		}
	}
	
	vTaskStartScheduler();
	/* Control never reaches here */
	while (1) {
	}
	return 0;
}
