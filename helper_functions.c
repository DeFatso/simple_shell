#include "main.h"
/**
 * _strlen - custom made strlen
 * @str: parameter-> string
 * Return: length of str
 */
size_t _strlen(const char *str)
{
	size_t length = 0;

	while (str[length] != '\0')
	{
		length++;
	}
	return (length);
}
