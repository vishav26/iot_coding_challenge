/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

/**
 * Example task of using USART_0 to echo using the IO abstraction.
 */
void USART_0_example_task(void *p)
{
	struct io_descriptor *io;
	uint16_t              data;

	(void)p;

	usart_os_get_io(&USART_0, &io);

	for (;;) {
		if (io->read(io, (uint8_t *)&data, 1) == 1) {
			io->write(io, (uint8_t *)&data, 1);
		}
	}
}

/**
 * Example task of using EDBG_COM to echo using the IO abstraction.
 */
void EDBG_COM_example_task(void *p)
{
	struct io_descriptor *io;
	uint16_t              data;

	(void)p;

	usart_os_get_io(&EDBG_COM, &io);

	for (;;) {
		if (io->read(io, (uint8_t *)&data, 1) == 1) {
			io->write(io, (uint8_t *)&data, 1);
		}
	}
}

/**
 * Example of using WDT_0.
 */
void WDT_0_example(void)
{
	uint32_t clk_rate;
	uint16_t timeout_period;

	clk_rate       = 1000;
	timeout_period = 4096;
	wdt_set_timeout_period(&WDT_0, clk_rate, timeout_period);
	wdt_enable(&WDT_0);
}
