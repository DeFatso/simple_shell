#include "shell.h"

/**
 * main - a simple shell
 * @ac: arg count
 * @av: arg vector
 * Return: 0
 */

int main(int ac, char *av[])
{
	pid_t childpid;
	ssize_t nread = 0;
	size_t len;
	int status, pipe;
	char ex[] = "exit", cmd_path[100], *line = NULL, **cmd_vector;

	if (ac > 1)
		return (0);

	pipe = isatty(STDIN_FILENO);
	while (1)
	{
		if (pipe)
		{
			if (prompt() == -1)
				continue;
		}

		if ((nread = getline(&line, &len, stdin)) == -1)
		{
			exit(EXIT_SUCCESS);
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		if (_strcmp(line, ex) == 0)
			return (0);

		if ((cmd_vector = tokenise(line)) == NULL)
			continue;

		free(line);

		if (search_paths(cmd_vector[0], cmd_path) == -1)
		{
			write(2, av[0], _strlen(av[0]));
			write(2, ": 1: ", 5);
			write(2, cmd_vector[0], _strlen(cmd_vector[0]));
			write(2, ": not found\n", 12);
			if (pipe == 0)
				exit(127);
			continue;
		}

		childpid = fork();

		if (childpid == -1)
		{
			perror("Failed to fork\n");
			exit(EXIT_FAILURE);
		}
		if (childpid == 0)
		{
			if (execve(cmd_path, cmd_vector, environ) == -1)
			{
				perror("Failed to execute command");
				free_array(cmd_vector);
				exit(EXIT_FAILURE);
			}
		}
		if (childpid > 0)
		{
			wait(&status);
			free_array(cmd_vector);
		}
	}
	return (0);
}
