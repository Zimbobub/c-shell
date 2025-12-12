#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


#define SH_TOK_BUFSIZE 64







// moves along until it finds a char from `delim`, then replaces it with \0, and returns the pointer to the start of the next token
// consumes successive delimiters until a non delim char is found
char* strtok(char* line, size_t start_offset) {
    // printf("strtok\n");

    bool found_end = false;
    size_t pos = start_offset;

    while (1) {
        // char c = line[pos];

        switch (line[pos]) {
            case ' ':
            case '\t':
            case '\r':
            case '\n':
            case '\a':
                line[pos] = '\0';
                found_end = true;
                break;

            case '\0':
                // if (found_end) return NULL; // no more tokens after
                return NULL;
                break;
            default:
                if (found_end) return line + pos;
                break;
        }

        pos++;
    }

}





char** sh_split_line(char* line) {
    printf("sh_split_line\n");
    size_t buf_size = SH_TOK_BUFSIZE;

    char** argv = malloc(buf_size * sizeof(char*));
    size_t position = 1;

    if (!argv) {
        fprintf(stderr, "sh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    // first arg starts at the start
    argv[0] = line;

    char* token;
    do {
        printf("%i", argv[position-1] - line);
        token = strtok(line, argv[position-1] - line);
        if (token == NULL) break;

        argv[position] = token;
        position++;

        // need to expand buf
        if (position == buf_size-2) {
            buf_size += SH_TOK_BUFSIZE;
            argv = realloc(argv, buf_size * sizeof(char*));
            if (!argv) {
                fprintf(stderr, "sh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    } while (1);
    
    argv[position] = NULL;

    return argv;
}

