#ifndef MAIN_H
#define MAIN_H

/*headerfiles*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

/*prototypes*/
int prompt(void);

/*helper functions*/
size_t _strlen(const char *str);
char *_strcpy(char *dest, const char *src);
char *_strdup(const char *str);
int _strcmp(const char *str1, const char *str2);



#endif
