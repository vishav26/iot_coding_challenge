/*
 * uart_task.c
 *
 * Created: 02/07/2019 06:35:10
 *  Author: VishavVishav
 */ 
#include <uart_task.h>
#include <atmel_start.h>

void helloTask(void *p)
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