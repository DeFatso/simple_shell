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
	size_t path_len;

	if (create_path_array(path_array) == -1)
		return (-1);

	getcwd(cwd, 100);
	while (path_array[i])
	{
		/* change working dir to path to be searched */
		if (chdir(path_array[i]) == -1)
		{
			perror("Failed to check path %s\n");
			free(path_array);
			return (-1);
		}

		/* check for file in path */
		found = stat(command, &file_info);
		if (found == 0)
		{
			/* save path in which it was found and return to original cwd */
			getcwd(cmd_abs_path, 100);
			if (chdir(cwd) == -1)
			{
				perror("Failed to return to cwd\n");
				free(path_array);
				return (-1);
			}
			path_len = strlen(cmd_abs_path);
			cmd_abs_path[path_len] = '/';
			cmd_abs_path = strcat(cmd_abs_path, command);
			free(path_array);
			return (0);
		}
		i++;
	}

	if (chdir(cwd) == -1)
	{
		perror("Failed to return to cwd\n");
		free(path_array);
		return (-1);
	}
	free(path_array);
	return (-1);
}

/**
 * create_path_array - creates an array of paths from PATHS env var
 * @path_array: buffer to store the array of paths
 * Return: array of paths
 */

int create_path_array(char **path_array)
{
	size_t path_count = 1, i = 0;
	char *dup_paths, *path, *delim = ":";

	/* search for path variable in environ and duplicate into a buffer */
	while (environ[i])
	{
		if (strncmp("PATH", environ[i], 4) == 0)
		{
			dup_paths = strdup(environ[i]);
		}
		i++;
	}

	/* count number of paths in path variable */
	i = 0;
	while (dup_paths[i])
	{
		if (dup_paths[i] == ':')
			path_count++;
		i++;
	}

	/* allocat memory for path_array */
	path_array = malloc((path_count + 1) * sizeof(char *));
	if (path_array == NULL)
	{
		perror("Failed to allocate memory for path_array");
		return (-1);
	}

	/* tokenize the buffer into individual paths and store in path_array */
	i = 0;
	path = strtok(dup_paths, delim);
	path_array[i++] = strdup(path + 5);
	while (path != NULL)
	{
		path = strtok(NULL, delim);
		if(path != NULL)
			path_array[i++] = strdup(path);
	}
	path_array[i] = NULL;
	free(dup_paths);

	return (path_array);
}
