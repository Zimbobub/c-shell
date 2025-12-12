
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



char* sh_read_line() {
    const size_t BLOCK_SIZE = 128;

    size_t capacity = BLOCK_SIZE;
    size_t len = 0;
    char* buffer = malloc(BLOCK_SIZE);

    if (!buffer) {
        printf("Failed to allocate command buffer");
        exit(1);
    }

    // read whatever is left in the capacity
    while (fgets(buffer + len, (int)(capacity - len), stdin)) {
        // (buffer + len) is the string starting from where we just added
        len += strlen(buffer + len);

        // len > 0 is just to prevent reading outside the buffer
        // check if last char is a \n, that means we're done
        if (len > 0 && buffer[len-1] == '\n') break;

        // need more room
        capacity += BLOCK_SIZE;
        char *tmp = realloc(buffer, capacity);
        if (!tmp) {
            printf("Failed to reallocate command buffer");
            free(buffer);
            exit(1);
        }
        buffer = tmp;
    }

    // if empty, return null ptr
    if (len == 0 && feof(stdin)) {
        free(buffer);
        return NULL;
    }
    // ensure null terminated
    // buffer[len] = '\0';
    return buffer;
}
