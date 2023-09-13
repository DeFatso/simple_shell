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
/**
 * _strdup - custom _strdup
 * @str: parameter string
 * Return: duplicate
 */
char *_strdup(const char *str)
{
	size_t len;
	char *duplicate;

	if (str == NULL)
	{
		return (NULL);
	}

	len = _strlen(str) + 1;
	duplicate = (char *)malloc(len);

	if (duplicate == NULL)
	{
		return (NULL);
	}

	_strcpy(duplicate, str);
	return (duplicate);
}
/**
 * _strcpy - custom strcpy
 * @dest: parameter -> destination
 * @src: parameter -> source
 * Return: destination string
 */
char *_strcpy(char *dest, const char *src)
{
	char *destination;

	if (dest == NULL || src == NULL)
	{
		return (NULL);
	}

	destination = dest;

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';
	return (destination);
}

/**
 * _strcmp - custom strcmp
 * @str1: first string
 * @str2: second string
 * Return: int
 */
int _strcmp(const char *str1, const char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}

	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}
