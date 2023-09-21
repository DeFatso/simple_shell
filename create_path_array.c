#include "shell.h"

/**
 * create_path_array - creates an array of paths from PATHS env var
 * Return: pointer to array of paths
 */

char **create_path_array(void)
{
	size_t path_count = 1, i = 0;
	char *dup_paths, *path, *delim = ":";
	char **path_array;

	while (environ[i])
	{
		if (_strncmp("PATH", environ[i], 4) == 0)
		{
			dup_paths = _strdup(environ[i]);
		}
		i++;
	}
	i = 0;
	while (dup_paths[i])
	{
		if (dup_paths[i] == ':')
			path_count++;
		i++;
	}
	path_array = malloc((path_count + 1) * sizeof(char *));
	if (path_array == NULL)
	{
		perror("Failed to allocate memory for path_array");
		return (NULL);
	}
	i = 0;
	path = _strtok(dup_paths, delim);
	path_array[i++] = _strdup(path + 5);
	while (path != NULL)
	{
		path = _strtok(NULL, delim);
		if (path != NULL)
			path_array[i++] = _strdup(path);
	}
	path_array[i] = NULL;
	free(dup_paths);
	return (path_array);
}
