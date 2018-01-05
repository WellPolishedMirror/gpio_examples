/*
 * Creates a polled-mode lister for a button on pin 17, 27, and 22.
 */

#include <linux/gpio.h>
#include <sys/ioctl.h>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

#include <unistd.h>

int main(int argc, char* argv[]) {
	int fd, i, j, k, temp;
	struct gpiohandle_request handle;
	struct gpiohandle_data data;

	static char* name = "Button example";

	fd = open("/dev/gpiochip0", O_RDONLY);
	/* List out the gpiopins to use */
	handle.lineoffsets[0] = 17;
	handle.lineoffsets[1] = 27;
	handle.lineoffsets[2] = 22;	

	/* Set flags for gpio lines */
	handle.flags = GPIOHANDLE_REQUEST_INPUT; 
	
	/* No need for default values. */

	/* Name the collection of GPIOs */
	for (i = 0; i < 15; i++)
		handle.consumer_label[i] = name[i];

	/* The number of lines */
	handle.lines = 3;

	/* The file descriptor will be populated after IOCTL request */
	handle.fd = 0;	

	fd = open("/dev/gpiochip0", O_RDONLY);
	
	if (ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &handle) == -1) {
		perror("Error getting handle" );
		return -1;
	}

	if (handle.fd == 0) {
		fprintf(stderr, "Error getting handler\n");
		return -1;
	}

	while(1) {
		data.values[0] = 0;
		data.values[1] = 0;
		data.values[2] = 0;
		if (ioctl(handle.fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data) == -1) {
			perror("Error setting gpios" );
			return -1;
		}

		if (data.values[0] == 1)
			printf("Button 17 pressed.\n");
		if (data.values[1] == 1)
			printf("Button 27 pressed.\n");
		if (data.values[2] == 1)
			printf("Button 22 pressed.\n");
		usleep(250000);
	}
	return 0;
}	
