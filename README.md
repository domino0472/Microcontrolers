# Microcontrollers - Embedded C labs
 
Microcontroller / embedded programming in **C**, developed during the *Microprocessor Technology* course (Technical Computer Science, Wrocław University of Science and Technology) and self-study.
 
> `AVR ATmega32`
 
## Topics covered
- GPIO - LEDs, buttons / digital inputs
- Timers & counters, hardware interrupts
- Serial communication (UART)

 
## Structure
- `Lab4/`, `Lab_5/`, `Lab 6/` - lab exercises
- `wyklad/` - lecture notes / example code
 
## Build & run
Przykład dla AVR + avr-gcc:
```
avr-gcc -mmcu=atmega328p -Os main.c -o main.elf
avr-objcopy -O ihex main.elf main.hex
avrdude -c <programmer> -p m328p -U flash:w:main.hex
```
 
## Tech
C · `[MCU]` · timers · interrupts · UART
