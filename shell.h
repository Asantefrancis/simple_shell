#ifndef SHELL_H
#define SHELL_H

#define BUFFER_SIZE 1024

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

void prompt_user(void);
void read_cmd(char **command);
void execute_cmd(char *command);

#endif
