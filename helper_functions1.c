#include "shell.h"
/**
 * _strncmp - custom strncmp
 * @s1: string 1
 * @s2: string 2
 * @n: he maximum number of characters to compare.
 * Return: returns 0 if strings are equal upto n
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0 && *s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
		n--;
	}

	if (n == 0)
	{
		return 0;
	}
	else
	{

		return (*(unsigned char *)s1 - *(unsigned char *)s2);
	}
}
