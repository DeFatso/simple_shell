#include "shell.h"

/**
 * get_command - gets command tokenises into an array
 * Return: pointer to array of command or NULL on failure
 */

char **get_command(void)
{
	char *line = NULL, **cmd_arr, ex[] = "exit";
	ssize_t nread = 0;
	size_t len;

	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
		free(line);
		exit(EXIT_SUCCESS);
	}

	if (line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	if (_strcmp(line, ex) == 0)
	{
		free(line);
		exit(EXIT_SUCCESS);
	}

	cmd_arr = tokenise(line);
	if (cmd_arr == NULL)
	{
		free(line);
		return (NULL);
	}
	free(line);

	return (cmd_arr);
}
