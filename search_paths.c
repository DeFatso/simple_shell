#include "shell.h"

/**
 * search_paths - searches for a command in paths contained in env
 * @command: command to be searched
 * @cmd_abs_path: buffer to store the absolute path of the cmd when found
 * Return: 0 if command is found and -1 if not
 */


int search_paths(char *command, char *cmd_abs_path)
{
	struct stat file_info;
	int found, i = 0;
	char cwd[100], **path_array = NULL;

	/* Check if command passed is contains full path already */
	if (stat(command, &file_info) == 0)
	{
		_strcpy(cmd_abs_path, command);
		return (0);
	}

	path_array = create_path_array();
	if (path_array == NULL)
		return (-1);

	getcwd(cwd, 100);
	while (path_array[i])
	{
		/* change working dir to path to be searched */
		if (chdir(path_array[i]) == -1)
		{
			free_array(path_array);
			return (-1);
		}

		/* check for file in path */
		found = stat(command, &file_info);
		if (found == 0)
		{
			/* save path in which it was found and return to original cwd */
			getcwd(cmd_abs_path, 90);
			if (chdir(cwd) == -1)
			{
				perror("Failed to return to cwd\n");
				free_array(path_array);
				return (-1);
			}
			_strcat(cmd_abs_path, "/");
			_strcat(cmd_abs_path, command);
			free_array(path_array);
			return (0);
		}
		i++;
	}

	if (chdir(cwd) == -1)
	{
		perror("Failed to return to cwd\n");
		free_array(path_array);
		return (-1);
	}
	free_array(path_array);
	return (-1);
}

/**
 * create_path_array - creates an array of paths from PATHS env var
 * @path_arr: buffer to store the array of paths
 * Return: 0 on success and -1 on failure
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
