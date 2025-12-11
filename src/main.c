#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"



char cmd_buffer[1024];


int main(int argc, char **argv) {
    // Load config files, if any.

    // Run command loop.
    sh_loop();

    // Perform any shutdown/cleanup.

    return EXIT_SUCCESS;
}


void sh_loop(void) {
    char *line;
    char **args;
    int status;

    do {
        printf("> ");
        line = sh_read_line();
        args = sh_split_line(line);
        status = sh_execute(args);

        free(line);
        free(args);
    } while (status);
}


