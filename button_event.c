/*
 * Creates a interrupt-driven lister for a button on pin 17.
 */

#include <linux/gpio.h>
#include <sys/ioctl.h>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

#include <unistd.h>

int main(int argc, char* argv[]) {
	int fd, i;
	struct gpioevent_request event;
	struct gpioevent_data data;

	static char* name = "Button event example";

	fd = open("/dev/gpiochip0", O_RDONLY);
	/* List out the gpiopin to use */
	event.lineoffset = 17;

	/* Set handle flag for gpio line */
	event.handleflags = GPIOHANDLE_REQUEST_INPUT; 
	
	/* Set the event to listen for */
	event.eventflags= GPIOEVENT_REQUEST_RISING_EDGE;

	/* Name the collection of GPIOs */
	for (i = 0; i < 21; i++)
		event.consumer_label[i] = name[i];

	/* The file descriptor will be populated after IOCTL request */
	event.fd = 0;	

	fd = open("/dev/gpiochip0", O_RDONLY);
	
	if (ioctl(fd, GPIO_GET_LINEEVENT_IOCTL, &event) == -1) {
		perror("Error getting event" );
		return -1;
	}

	if (event.fd == 0) {
		fprintf(stderr, "Error getting event listener\n");
		return -1;
	}

	i = 0;
	while(1) {
		/* Read blocks until event occurs. */
		read(event.fd, &data, sizeof(struct gpioevent_data));
		/* timestamp and id does not seem to give useful information */
		// printf("Button pressed at %x, event id: %d\n", data.timestamp, data.id);
		/* No need to sleep as blocking occurs */
		// sleep(1);
		printf("Button 17 pressed: %4d\n", ++i);
	}
	return 0;
}	
