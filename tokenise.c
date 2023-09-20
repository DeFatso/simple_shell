#include "shell.h"

/**
 * tokenise - converts the command line into an array of command args
 * @cmd_line: the line of command inputed
 * Return: pointer to the array of command args
 */

char **tokenise(char *cmd_line)
{
	char *tok, **command, delim[] = " \t\n\r";
	size_t i = 0, count = 0;

	/* count number of args in command given */
	while (cmd_line[i])
	{
		if ((cmd_line[i] == ' ' && cmd_line[i + 1] != ' ') || !cmd_line[i + 1])
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
