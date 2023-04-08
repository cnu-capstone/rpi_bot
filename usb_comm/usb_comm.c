#include <stdio.h>
#include "pico/stdlib.h"

// # define LED_PIN 22
# define SUCCESS 0
# define CMD_LEN 8

void enqueue(char* data, char* buff) {
    for (int i = 0; i < CMD_LEN; i++) {
        *(buff++) = *(data+i);  // Dereference data at position i and store into buff and increment buff position
    }
}

void read_stream(char* buff) {
    // char command[CMD_LEN];

    scanf("%8s", buff);

    printf("Data received: %s\n", buff);

    // enqueue(command, buff);
    
    // return command;
}

int main() {
    stdio_init_all();

    char buffer[1024];
    char cmd[CMD_LEN];

    while(1) {
        for (int i = 0; i < (sizeof(buffer)/sizeof(char))/CMD_LEN; i++) {
            read_stream(cmd);
            // scanf("%8s", cmd);
            // enqueue(cmd, buffer);
            // printf("Data received: %s\n", cmd);
            sleep_ms(500);
        }
    }
    return SUCCESS;
}