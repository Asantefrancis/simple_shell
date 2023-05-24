#ifndef SHELL_H
#define SHELL_H

#define BUFFER_SIZE 1024

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

void prompt_user(void);
void read_cmd(char *cmd);
void execute_cmd(char *cmd);

#endif
