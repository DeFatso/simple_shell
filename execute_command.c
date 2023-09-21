#include "shell.h"

/**
 * execute - forks and executes a command
 * @cmd: command to be executed
 * @cmd_vec: array of command with arguements
 * Return: void
 */

void execute(char *cmd, char *cmd_vec[])
{
	pid_t childpid;
	int status;

	childpid = fork();
	if (childpid == -1)
	{
		perror("Failed to fork\n");
		exit(EXIT_FAILURE);
	}
	if (childpid == 0)
	{
		if (execve(cmd, cmd_vec, environ) == -1)
		{
			perror("Failed to execute command");
			free_array(cmd_vec);
			exit(EXIT_FAILURE);
		}
	}
	if (childpid > 0)
	{
		wait(&status);
		free_array(cmd_vec);
	}
}
