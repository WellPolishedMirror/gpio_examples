/*
 *
 * #define GPIO_GET_LINEINFO_IOCTL _IOWR(0xB4, 0x02, struct gpioline_info)
 *
 */
#include <linux/gpio.h>
#include <sys/ioctl.h>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

/**
 * struct gpioline_info - Information about a certain GPIO line
 * @line_offset: the local offset on this GPIO device, fill this in when
 * requesting the line information from the kernel
 * @flags: various flags for this line
 * @name: the name of this GPIO line, such as the output pin of the line on the
 * chip, a rail or a pin header name on a board, as specified by the gpio
 * chip, may be NULL
 * @consumer: a functional name for the consumer of this GPIO line as set by
 * whatever is using it, will be NULL if there is no current user but may
 * also be NULL if the consumer doesn't set this up
 */


int main(int argc, char* argv[]) {
	struct gpiochip_info chip;
	struct gpioline_info line;
	int fd, i;

	fd = open("/dev/gpiochip0", O_RDONLY);
	
	if (ioctl(fd, GPIO_GET_CHIPINFO_IOCTL, &chip) == -1) {
		perror("Error getting chip info." );
		return -1;
	}

	printf("=== /dev/gpiochip0 === \nname: %s\nlabel: %s\nlines: %d\n", chip.name, chip.label, chip.lines);


	for (i = 0; i < chip.lines; i++) {
		line.line_offset = i;
		if (ioctl(fd, GPIO_GET_LINEINFO_IOCTL, &line) == -1) {
			perror("Error getting line info");
			return -1;
		}
		printf("\t(%d) line: %d\n\t(%d) flags: %d\n\t(%d) name: %s\n\t(%d) consumer: %s\n", i, line.line_offset, i, line.flags, i, line.name, i, line.consumer);
	}
	return 0;
}	
