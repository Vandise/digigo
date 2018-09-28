#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <sys/ioctl.h>

#define DEBUG 1
#define TRUE 1
#define FALSE 0

char *portname = "/dev/cu.usbmodem1411";
int fd, n, i;
char buf[64] = "empty";
struct termios toptions;

int fd_opened() {
  if (fd < 0) {
    return FALSE;
  }
  return TRUE;
}

void open_fd() {
  fd = open(portname, O_RDWR | O_NOCTTY);
  if (fd < 0) {
    printf("error %d opening %s: %s", errno, portname, strerror (errno));
  }
}

void setup_serial_port() {
  /* get current serial port settings */
  tcgetattr(fd, &toptions);

  /* set 9600 baud both ways */
  cfsetispeed(&toptions, B9600);
  cfsetospeed(&toptions, B9600);

  /* 8 bits, no parity, no stop bits */
  toptions.c_cflag &= ~PARENB;
  toptions.c_cflag &= ~CSTOPB;
  toptions.c_cflag &= ~CSIZE;
  toptions.c_cflag |= CS8;

  /* Canonical mode */
  toptions.c_lflag |= ICANON;

  /* commit the serial port settings */
  tcsetattr(fd, TCSANOW, &toptions);
}

int main(int argc, char *argv[]) {
  // open the serial port
  open_fd();
  if (!fd_opened()) {
    return 1;
  }

  // wait for the chip to reboot
  sleep(2);

  // configure the serial port settings
  setup_serial_port();

  /* Send byte to trigger Arduino to send string back */
  write(fd, "0", 1);

  /* Receive string from Arduino */
  n = read(fd, buf, 64);

  /* insert terminating zero in the string */
  buf[n] = 0;

  printf("%i bytes read, buffer contains: %s\n", n, buf);

  if(DEBUG) {
    printf("Printing individual characters in buf as int \n\n");
    for(i=0; i<n; i++) {
      printf("Byte %i:%i, ",i+1, (int)buf[i]);
    }
    printf("\n");
  }
  return 0;
}