#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - executes commands written on stdin
 * Return: 0
 */

int main(void)
{
	pid_t proc;
	int status, j;
	size_t len, size = 0, ccount, i;
	char **argv;
	char *cmd, *command = NULL, ex[] = "exit";

	while (1)
	{
		printf("simple_shell$ ");
		if (getline(&command, &size, stdin) == -1)
		       perror("!Error reading command!\n");

		len = strlen(command);
		if (command[len-1] == '\n')
			command[len-1] = '\0';

		if (strcmp(command, ex) == 0)
		{
			return (0);
		}

		/* count number of commands given */
		i = 0;
		ccount = 0;
		while (command[i])
		{
			if ((command[i] == ' ' && command[i+1] != ' ') || !(command[i+1]))
				ccount++;
			i++;
		}

		argv = malloc(sizeof(char *) * (ccount + 1));
		if (argv == NULL)
		{
			perror("!Failed to alloc memory for command!\n");
			return (1);
		}

		i = 0;
		cmd = strtok(command, " ");
		argv[i++] = strdup(cmd);

		while (i < ccount)
		{
			cmd = strtok(NULL, " ");
			argv[i++] = strdup(cmd);
		}
		argv[i] = NULL;

		proc = fork();
		if (proc == -1)
		{
			perror("!failed to create process!\n");
			return (1);
		}
		else if (proc == 0)
		{
			if (execve(argv[0], argv, NULL) == -1)
			{
				perror("!failed to execute command!\n");
			}
			exit(2);
		}
		else
		{
			wait(&status);
			printf("command exec success :)\n");
			j = i;
			free(command);
			while (j >= 0)
				free(argv[j--]);
			free(argv);
		}
	}
	return (0);
}
