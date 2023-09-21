#include "shell.h"

/**
 * main - a simple shell
 * @ac: arg count
 * @av: arg vector
 * Return: 0
 */

int main(int ac, char *av[])
{
	int pipe;
	char cmd_path[100], **cmd_vector;

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

		cmd_vector = get_command();
		if (cmd_vector == NULL)
			continue;

		if (search_paths(cmd_vector[0], cmd_path) == -1)
		{
			write(2, av[0], _strlen(av[0]));
			write(2, ": 1: ", 5);
			write(2, cmd_vector[0], _strlen(cmd_vector[0]));
			write(2, ": not found\n", 12);
			free_array(cmd_vector);
			if (pipe == 0)
				exit(127);
			continue;
		}

		execute(cmd_path, cmd_vector);
	}
	return (0);
}
