#include "shell.h"

/**
 * main - a simple shell
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
			write(2, line, _strlen(line));
			write(2, " not found\n", 11);
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

/**
 * tokenise - converts the command line into an array of command args
 * @cmd_line: the line of command inputed
 * @count: pointer to number of arguements 
 * Return: pointer to the array of command args
 */

char **tokenise(char *cmd_line)
{
	char *tok, **command, delim[] = " \t\n\r";
	size_t i = 0, count = 0;

	/* count number of args in command given */
	while (cmd_line[i])
	{
		if ((cmd_line[i] == ' ' && cmd_line[i+1] != ' ') || !cmd_line[i+1])
			count++;
		i++;
	}

	command = malloc((count + 1) * sizeof(char *));
	if (command == NULL)
	{
		perror("Failed to allocate memory for command\n");
		return (NULL);
	}

	i = 0;
	tok = _strtok(cmd_line, delim);
	command[i++] = _strdup(tok);
	while (i < count)
	{
		tok = _strtok(NULL, delim);
		command[i++] = _strdup(tok);
	}
	command[i] = NULL;

	if (command[0] == NULL)
	{
		free_array(command);
		return (NULL);
	}

	return (command);
}

/**
 * free_array - frees the memory allocated to an array of strings
 * @arr: pointer to array to be freed
 * Return: 0 on success and -1 on failure
 */

int free_array(char **arr)
{
	size_t count = 0;

	while (arr[count])
		count++;

	while (count > 0)
	{
		free(arr[count - 1]);
		count--;
	}
	free(arr);

	return (0);
}
