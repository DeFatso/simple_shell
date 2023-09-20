#include "shell.h"

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
