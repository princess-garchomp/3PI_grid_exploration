#all: main.o IR_reflect.o motor.o push_button_A.o radio_IO.o 
all: main.o main.hex flash clean

main.o:
	avr-gcc -mmcu=atmega328p main.c IR_reflect.c motor.c push_button_A.c radio_IO.c  -o main.out
IR_reflect.o:
	avr-gcc -mmcu=atmega328p IR_reflect.c  -o IR_reflect.out
motor.o:
	avr-gcc -mmcu=atmega328p motor.c -o motor.out

push_button_A.o:
	 avr-gcc -mmcu=atmega328p push_button_A.c -o push_button_A.out
radio_IO.o:
	avr-gcc -mmcu=atmega328p radio_IO.c -o radio_IO.out

main.hex:
	avr-objcopy -j .text -j .data -O ihex main.out main.hex
flash:
	sudo avrdude -P /dev/ttyACM0 -b 57600 -p m328p -c STK500 -F -e -U flash:w:main.hex
clean_.out:
	rm -rf *.out
clean:
	rm -rf *.hex
	rm -rf *.out


#ls /dev/ttyACM*
# this checks what USB port the programmer is plugged into
