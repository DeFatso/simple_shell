#include "shell.h"

/**
 * search_paths - searches for a command in paths contained in env
 * @command: command to be searched
 * Return: 0 if file is found and -1 if not
 */

int search_paths(char *command, char *cmd_abs_path)
{
	struct stat file_info;
	int found, i = 0;
	char cwd[100], **path_array;
	size_t path_len;

	path_array = create_path_array();

	getcwd(cwd, 100);
	while (path_array[i])
	{
		/* change working dir to path to be searched */
		if (chdir(path_array[i]) == -1)
		{
			perror("Failed to check path %s\n");
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
				return (-1);
			}
			path_len = strlen(cmd_abs_path);
			cmd_abs_path[path_len] = '/';
			cmd_abs_path = strcat(cmd_abs_path, command);
			return (0);
		}
		i++;
	}

	if (chdir(cwd) == -1)
	{
		perror("Failed to return to cwd\n");
		return (-1);
	}
	return (-1);
}

/**
 * create_path_array - creates an array of paths from PATHS env var
 * Return: array of paths
 */

char **create_path_array(void)
{
	size_t path_count = 1, i = 0;
	char *dup_paths, *path, *delim = ":";
	char **path_array = NULL;

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
		exit(EXIT_FAILURE);
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
	free(dup_paths);

	return (path_array);
}
