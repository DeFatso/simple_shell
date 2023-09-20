#include "shell.h"
/**
 * run_shell - runs shell
 */
void run_shell(void)
{
	char ex[] = "exit";
	char *line = NULL;
	size_t len = 0;
	int pipe;

	while (1)
	{
		pipe = isatty(STDIN_FILENO);

		if (pipe && prompt() == -1)
			continue;

		if (getline(&line, &len, stdin) == -1)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}

		if (line[_strlen(line) - 1] == '\n')
			line[_strlen(line) - 1] = '\0';

		if (_strcmp(line, ex) == 0)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}

		process_input(line);
		free(line);
	}
}

/**
 * process_input - process input
 * @input: input
 */
void process_input(char *input)
{
	char **cmd_vector = tokenise(input);
	char cmd_path[100];

	if (cmd_vector == NULL)
		return;

	if (search_paths(cmd_vector[0], cmd_path) == -1)
	{
		handle_command_not_found(cmd_vector[0]);
		return;
	}

	execute_command(cmd_path, cmd_vector);
	free_array(cmd_vector);
}

/**
 * execute_command - execute_command
 * @cmd_path: cmd_path
 * @cmd_vector: cmd_vector
 */
void execute_command(const char *cmd_path, char *const cmd_vector[])
{
	pid_t childpid = fork();
	int status;

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

	status;
	wait(&status);
	free_array(cmd_vector);
}
/**
 * handle_command_not_found - handle_command_not_found
 * @cmd: command
 */
void handle_command_not_found(const char *cmd)
{
	write(2, av[0], _strlen(av[0]));
	write(2, ": 1: ", 5);
	write(2, cmd, _strlen(cmd));
	write(2, ": not found\n", 12);
}

/**
 * main - entry point
 * @ac: argc
 * @av: argv
 * Return: 0
 */
int main(int ac, char *av[])
{
	if (ac > 1)
		return (0);

	run_shell();
	return (0);
}
