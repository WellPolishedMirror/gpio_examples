#include <linux/gpio.h>
#include <sys/ioctl.h>

#include <errno.h>
#include <fcntl.h>

#include <stdio.h>


/**
 * struct gpiochip_info - Information about a certain GPIO chip
 * @name: the Linux kernel name of this GPIO chip
 * @label: a functional name for this GPIO chip, such as a product
 * number, may be NULL
 * @lines: number of GPIO lines on this chip
 */

int main(int argc, char* argv[]) {
	struct gpiochip_info chip;
	int fd;

	fd = open("/dev/gpiochip0", O_RDONLY);
	
	if (ioctl(fd, GPIO_GET_CHIPINFO_IOCTL, &chip) == -1) {
		perror("Error getting chip info");
		return -1;
	}

	printf("=== /dev/gpiochip0 === \nname: %s\nlabel: %s\nlines: %d\n", chip.name, chip.label, chip.lines);

	return 0;
}	
