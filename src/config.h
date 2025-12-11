#pragma once

#include "shell.h"

typedef struct {
    Command prompt;
} Config;



Config read_config(char* path);