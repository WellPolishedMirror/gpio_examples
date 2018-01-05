all: button_event button_poll blink lsgpio chipinfo

chipinfo: chipinfo.c
	gcc -o chipinfo chipinfo.c

lsgpio: lsgpio.c
	gcc -o lsgpio lsgpio.c

blink: blink.c
	gcc -o blink blink.c

button_poll: button_poll.c
	gcc -o button_poll button_poll.c

button_event: button_event.c
	gcc -o button_event button_event.c

clean:
	rm -vf button_poll button_event blink chipinfo gpiohandle_example lsgpio
