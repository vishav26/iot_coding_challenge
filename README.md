
* This is the readme file for the iot solution
# Description

## Hardware used:
Atmel SAME54 Xplained Board

RS232 to FTDI Board

## Software Components
RTOS v10.0.0

USART0

WDT

Teraterm for Serial port Console

## Hardware Setup
1. Power the board using USB
2. Connect PA04(Ext1) pin to RX of FTDI and PA05(Ext1) pin to TX of FTDI
3. Setup the terminal using Teraterm with baud rate 9600.

## Software Setup

The system currently consists of two tasks:

The first task(console_task) prints Hello Dott!! every 1s to uart console on host machine.

The second task (watchdog task) resets the watchdog timer every 1.5 second. The time-out period of the watchdog timer has been set to 2s.

Second task has a priority of IDLE_PRIORITY+2 and first task IDLE_PRIORITY+1

The application sequence is as follows:
1. First intiialization of mcu, Usart and Wdt is done.
2. Console and watchdog tasks are created.
3. The system starts with watchdog task. First check is whether the watchdog is already disabled. If no, then disable it.
4. Check if the Always on bit of watchdog is enabled is disabled. If not, disable it.
5. Set the timeout value. For current case it has been set o 2s.
6. Enable the Watchdog timer.
7. The watchdog timer is resetted every 1.5 seconds to prevent mcu from restarting.
8. The condsole task prints the message Hello Dott every 1 seconds.
