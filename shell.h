#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>

/* global var */
extern char **environ;

/* Prototypes */
int prompt(void);
char **tokenise(char *cmd_line);
int search_paths(char *command, char *cmd_abs_path);
char **create_path_array(void);
int free_array(char **arr);

/* helper functions */
size_t _strlen(const char *str);
char *_strcpy(char *dest, const char *src);
char *_strdup(const char *str);
int _strcmp(const char *str1, const char *str2);
char *_strchr(const char *str, int character);
char *_strtok(char *str, const char *delim);

#endif /* SHELL_H */
