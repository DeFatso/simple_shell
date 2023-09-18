#include "shell.h"
/**
 * prompt - prints the prompt using write system call
 * Return: returns 0 at success and -1 at failure
 */
int prompt(void)
{
	char *prompt = "sh$ ";
	size_t length;
	ssize_t bytes_written;

	length = _strlen(prompt);

	bytes_written = write(1, prompt, length);

	if (bytes_written == -1)
	{
		perror("Failed to write\n");
		return (-1);
	}

	return (0);
}
