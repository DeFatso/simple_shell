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
char *_strcat(char *dest, char *src);
size_t _strlen(const char *str);
char *_strcpy(char *dest, const char *src);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strdup(const char *str);
int _strcmp(const char *str1, const char *str2);
char *_strchr(const char *str, int character);
char *_strtok(char *str, const char *delim);

/*new prototypes*/
void handle_command_not_found(const char *cmd);
void execute_command(const char *cmd_path, char *const cmd_vector[]);
void process_input(char *input);
void run_shell(void);

#endif /* SHELL_H */
