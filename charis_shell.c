#include "shell.h"

/**
 * main - a simple shell
 * Return: 0
 */

int main(void)
{
	pid_t childpid;
	ssize_t nread = 0;
	size_t len;
	int status;
	char cmd_path[100], *line = NULL;

	while (1)
	{
		printf("Charisshell$ ");
		nread = getline(&line, &len, stdin);
		if (nread == -1)
			exit(1);

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		if (search_paths(line, cmd_path) == -1)
		{
			printf("command %s not found\n", line);
			return (-1);
		}
		printf("cmd path is > %s <\n", cmd_path);

		childpid = fork();

		if (childpid == -1)
		{
			perror("Failed to fork\n");
			free(line);
			exit(90);
		}
		else if (childpid == 0)
		{
			execute(cmd_path);
		}
		else
		{
			wait(&status);
		}

	}
	return (0);
}

/**
 * execute - executes a line of command
 * @line: the line of command to execute
 * Return: 0 on success -1 on failure
 */

int execute(char *line)
{
	char **command;

	command = malloc(sizeof(char *) * 2);
	if (command == NULL)
	{
		perror("Failed to allocate memory for command\n");
		return (-1);
	}

	command[0] = strdup(line);
	command[1] = NULL;
	if (execve(command[0], command, environ) == -1)
	{
		perror("Failed to execute command");
		free(command[0]);
		free(command);
		exit(EXIT_FAILURE);
	}
	return (0);
}
