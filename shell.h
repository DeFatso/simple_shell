#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
extern char **environ;
int execute(char *line);
int search_paths(char *command, char *cmd_abs_path);
int create_path_array(char **path_array);

#endif /*MAIN_H*/
