# STM32 basic software library

## General principle

The STM32 software library is intended to provide a full driver solution.
This generic library is a starting point where any application project can be based on.

It is divided into several submodules.

The low level drivers contains all microcontroler drivers divided into two specific classifications:
  - MCU is all the SOC related drivers (communication, timers, ...).
  - CPU is all the ARM core Cortex-M related drivers (NVIC, MPU, SYSTICK, ...).

Some drivers are divided into several *.c files regarding the mode the driver will be used.
For example a communication peripheral can be used in polling, interruption or DMA mode. It can be blocking or non blocking (synchronous/asynchronous).
The makefile will compile the expected file regarding the configuration generated.

The platform drivers are the drivers developped to address external component on the board. Like SPI, I2C peripheral (NVM, GPIO expander, anything ...).
These platform drivers will mostly use the low level drivers to control the MCU peripherals or to refer to MCU/CPU parameters.

The library provide tools to implement generic functionalities. This can be queues, mathematic functions or data types just to name a few.

![Global architecture overview](./01-documentation/global_architecture.drawio.svg)

The different modules are described in:

[Low level drivers](./01-documentation/low_level_drivers.md)

[Platform drivers](./01-documentation/platform_drivers.md)

[Library](./01-documentation/library.md)
