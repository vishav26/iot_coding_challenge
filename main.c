#include <atmel_start.h>

#include <wd_task.h>
#include <uart_task.h>


#define TASK_HELLO_STACK_SIZE (108 / sizeof(portSTACK_TYPE))
#define TASK_HELLO_STACK_PRIORITY (tskIDLE_PRIORITY + 1)

#define TASK_WD_STACK_SIZE (108 / sizeof(portSTACK_TYPE))
#define TASK_WD_STACK_PRIORITY (tskIDLE_PRIORITY + 2)

static TaskHandle_t xCreatedHelloTask;
static TaskHandle_t xCreatedWdTask;

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
