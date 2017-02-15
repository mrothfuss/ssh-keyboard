#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <termio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#include <linux/uinput.h>

static int fd;
static struct uinput_user_dev device;
static struct termios terminal;

static int running;

extern void send_ascii(char);

int init_device() {
	int i;

	fd = open("/dev/uinput", O_WRONLY | O_NDELAY);

	if(fd <= 0) {
		perror("unable to open /dev/uinput");
		return -1;
	}

	memset(&device, 0, sizeof(device));
	strncpy(device.name, "SSH Keyboard", UINPUT_MAX_NAME_SIZE);
	device.id.version = 4;
	device.id.bustype = BUS_USB;

	ioctl(fd, UI_SET_EVBIT, EV_KEY);
	ioctl(fd, UI_SET_EVBIT, EV_REL);
	ioctl(fd, UI_SET_RELBIT, REL_X);
	ioctl(fd, UI_SET_RELBIT, REL_Y);

	for(i = 0; i < 256; i++) {
		ioctl(fd, UI_SET_KEYBIT, i);
	}

	write(fd, &device, sizeof(device));

	if(ioctl(fd, UI_DEV_CREATE)) {
		perror("failed to create device");
		return -1;
	}

	return 0;
}

void cleanup_device() {
	ioctl(fd, UI_DEV_DESTROY);
	close(fd);
}

int init_terminal() {
	if(tcgetattr(0, &terminal) < 0) {
		perror("failed to get terminal attributes");
		return -1;
	}

	terminal.c_lflag &= ~ICANON;
	terminal.c_lflag &= ~ECHO;
	terminal.c_cc[VMIN] = 1;
	terminal.c_cc[VTIME] = 0;
	
	if(tcsetattr(0, TCSANOW, &terminal) < 0) {
		perror("failed to set terminal attributes");
	}

	return 0;
}

void cleanup_terminal() {
	terminal.c_lflag |= ICANON;
	terminal.c_lflag |= ECHO;
	if(tcsetattr(0, TCSADRAIN, &terminal) < 0) {
		perror("failed restoring the terminal attributes");
	}
}

void btn_on(int btn) {
	struct input_event event;

	memset(&event, 0, sizeof(event));
	gettimeofday(&event.time, NULL);
	event.type = EV_KEY;
	event.code = btn;
	event.value = 1;
	write(fd, &event, sizeof(event));

	event.type = EV_SYN;
	event.code = SYN_REPORT;
	event.value = 0;
	write(fd, &event, sizeof(event));
}

void btn_off(int btn) {
	struct input_event event;

	memset(&event, 0, sizeof(event));
	gettimeofday(&event.time, NULL);
	event.type = EV_KEY;
	event.code = btn;
	event.value = 0;
	write(fd, &event, sizeof(event));

	event.type = EV_SYN;
	event.code = SYN_REPORT;
	event.value = 0;
	write(fd, &event, sizeof(event));
}

static void handle(int sig) {
	printf("Signal Received\n");
	running = 0;
}

int main() {
	struct sigaction sa;
	char ascii;
	ssize_t length;

	running = 1;

	sa.sa_handler = handle;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if(sigaction(SIGINT, &sa, NULL) != 0) {
		perror("sigaction");
	}

	if(init_device()) return -1;

	if(init_terminal()) {
		cleanup_device();
		return -1;
	}

	for(;;) {
		length = read(STDIN_FILENO, &ascii, sizeof(ascii));
		if(running != 0) {
			break;
		}
		if(length <= 0) {
			break;
		}
		send_ascii(ascii);
	}

	cleanup_terminal();
	cleanup_device();

	return 0;
}
