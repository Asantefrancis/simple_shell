#ifndef SHELL_H
#define SHELL_H


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(int ac, char **av, char **env);
void prompt(char **av, char **env);
void child_process(char **av, char **env, char **argv);
void parent_process(int *status);

#endif
