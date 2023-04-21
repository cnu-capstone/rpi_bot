#include <stdio.h>
#include <unistd.h>  // Serial Bus R/W
#include <fcntl.h>  // TTY file control
#include <termios.h>  // Terminal control definitions
#include <errno.h>  // sterror() function
#include <string>
#include <iostream>
#include <cstring>

#include "../../includes/FileIO.h"  // File IO header

#define SUCCESS 0
#define SERIAL_ACCESS_ERR -1
#define TCGETATTR_ERR -2
#define TCSETATTR_ERR -3

#define UART_BAUDR B115200
#define MSG_SIZE 8
#define BUFFER_SIZE 1024

int main() {
	int uart_port = open("/dev/ttyACM0", O_RDWR);

	// Error handling for opening file stream
	if (uart_port < 0) {
		//printf("Error %i from open: %s\n", errno, sterror(errno));
		std::cout<<"Error opening file /dev/ttyACM0..."<<std::endl;
		return SERIAL_ACCESS_ERR;
	}
	
	struct termios tty;
	
	// Read in existing settings, and handle any error
	if (tcgetattr(uart_port, &tty) != 0) {
		//printf("Error %i from tcgetattr: %s\n", errno, sterror(errno));
		std::cout<<"Error getting tty attributes..."<<std::endl;
		return TCGETATTR_ERR;
	}
	
	// UART utilizes B115200 8N1
	// 8 Num Bits
	// No Parity
	// 1 Stop Bit
	
	tty.c_cflag &= ~PARENB;  // Clears Parity Bit
	tty.c_cflag &= ~CSTOPB;  // Clears stop field, 1 bit is used
	tty.c_cflag &= ~CSIZE; // Clear all bits that set the data size 
	tty.c_cflag |= CS8; // 8 bits per byte
	tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control
	tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines

	tty.c_lflag |= ICANON;  // Turns on canonical mode (newline termin.)
	tty.c_lflag &= ~ECHO; // Disable echo
	tty.c_lflag &= ~ECHOE; // Disable erasure
	tty.c_lflag &= ~ECHONL; // Disable new-line echo
	tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
	tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
	tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

	tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
	tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

	tty.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
	tty.c_cc[VMIN] = 0;

	// Set in/out baud rate to be 115200
	cfsetispeed(&tty, UART_BAUDR);
	cfsetospeed(&tty, UART_BAUDR);
	
	// Save tty settings, also checking for error
	if (tcsetattr(uart_port, TCSANOW, &tty) != 0) {
	  //printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
	  std::cout<<"Error setting tty attributes..."<<std::endl;
	  return TCGETATTR_ERR;
	}
	
	char msg[MSG_SIZE];
	
	//char buffer[BUFFER_SIZE];
	char read_buff[BUFFER_SIZE];
	
	//std::string msg_string = "011,0001";
	std::string msg_string;

	// AWS dropbox file
	std::string filepath = "/home/pi/Desktop/AWS/location.txt";
	
	// FileIO fio(filepath);
	
	while (1) {
		// std::cout<<"Please enter command: ";
		// std::cin>>msg_string;
		// std::cout<<std::endl;
		FileIO fio(filepath);

		bool read_success = fio.read(msg_string);

		std::cout<<msg_string<<std::endl;

		if (std::strcmp(msg_string.c_str(), "Forward") == 0) {  // If string is "Forward"
			msg_string = "11100001";
		}
		else if (std::strcmp(msg_string.c_str(), "Left") == 0) {  // If string is "Left"
			msg_string = "10100001";
		}
		else if (std::strcmp(msg_string.c_str(), "Right") == 0) {  // If string is "Right"
			msg_string = "11000001";
		}
		else if (std::strcmp(msg_string.c_str(), "Reverse") == 0) {  // If string is "Reverse"
			msg_string = "01100001";
		}
		else {
			msg_string = "10000000";
		}

		// fio.clear();
		
		strcpy(msg, msg_string.c_str());
		
		sleep(1);
		
		write(uart_port, msg, sizeof(msg));
		
		int bytes_read = read(uart_port, &read_buff, sizeof(read_buff));
		
		if (bytes_read < 0) {
			//printf("Error reading...\n");
			std::cout<<"Error reading data..."<<std::endl;
		}
		
		//printf("Read %i bytes. Received message: ", bytes_read);
		std::cout<<"Read "<<bytes_read<<" bytes. Received message: ";
		
		const char* char_p = &read_buff[0];
		
		for (int i = 0; i < bytes_read; i++) {
			std::cout<<*(char_p+i);
			//printf(*(char_p+i));
		}
		std::cout<<std::endl;
		//printf("\n");
	}
	
	close(uart_port);
	return SUCCESS;
}
