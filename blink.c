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

	static char* name = "Blink example";

	fd = open("/dev/gpiochip0", O_RDONLY);
	/* List out the gpiopins to use */
	handle.lineoffsets[0] = 14;
	handle.lineoffsets[1] = 15;
	handle.lineoffsets[2] = 18;
	
	/* Set flags for gpio lines */
	handle.flags = GPIOHANDLE_REQUEST_OUTPUT; 
	
	/* Set the default values 0 is low, 1 is high */
	handle.default_values[0] = 1;		
	handle.default_values[1] = 1;		
	handle.default_values[2] = 1;		

	/* Name the collection of GPIOs */
	for (i = 0; i < 14; i++)
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
	
	i = 1;
	j = 0;
	k = 0;
	while(1) {
		data.values[0] = i;
		data.values[1] = j;
		data.values[2] = k;
		if (ioctl(handle.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data) == -1) {
			perror("Error setting gpios" );
			return -1;
		}
		temp = i;
		i = k;
		k = j;	
		j = temp;
		usleep(200000);
	}
	return 0;
}	
