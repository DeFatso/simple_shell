#include "shell.h"
/**
 * _strtok - splits a string by some delimiter.
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: string splited.
 */
char *_strtok(char *str, const char *delim)
{
	static char *last_token;
	char *start, *end;

	if (str != NULL)
	{
		last_token = str;
	}
	if (last_token == NULL)
	{
		return (NULL);
	}

	start = last_token;
	while (*start && _strchr(delim, *start))
	{
		start++;
	}
	if (!*start)
	{
		last_token = NULL;
		return (NULL);
	}

	end = start + 1;
	while (*end && !_strchr(delim, *end))
		end++;

	if (*end)
		*end++ = '\0';

	last_token = end;
	return (start);
}

/**
 * _strchr - custom strchr
 * @str: string
 * @character: char you want to search for within the string
 * Return: pointer to the first occurrence of the specified char
 */
char *_strchr(const char *str, int character)
{
	while (*str != '\0')
	{
		if (*str == character)
		{
			return ((char *)str);
		}
		str++;
	}

	return (NULL);
}
