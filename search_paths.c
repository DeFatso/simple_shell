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
	char cwd[100], **path_array = NULL;
	int i;

	if (stat(command, &file_info) == 0)
	{
		_strcpy(cmd_abs_path, command);
		return (0);
	}
	path_array = create_path_array();
	if (path_array == NULL)
		return (-1);
	getcwd(cwd, 100);
	for (i = 0; (path_array[i]); i++)
	{
		chdir(path_array[i]);
		if (stat(command, &file_info) == 0)
		{
			getcwd(cmd_abs_path, 90);
			if (chdir(cwd) == -1)
			{
				free_array(path_array);
				return (-1);
			}
			_strcat(cmd_abs_path, "/");
			_strcat(cmd_abs_path, command);
			free_array(path_array);
			return (0);
		}
	}
	if (chdir(cwd) == -1)
	{
		free_array(path_array);
		return (-1);
	}
	free_array(path_array);
	return (-1);
}
