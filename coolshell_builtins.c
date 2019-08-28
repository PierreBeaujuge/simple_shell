#include "coolshell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>

/**
 * get_builtins_func - function that checks for built-ins and points to
 * the proper function pointer
 * @s: buffer string passed from main, based on user input
 * Return: NULL or pointer to the correct function
 */

void (*get_builtins_func(char *s))(char **, char *, char *, char **, int)
{
	built_ins bi[] = {
		{"env", env_},
		{"exit", exit_},
		{NULL, NULL}
	};
	int i = 0, j = 0, flag = 1, len1 = 0, len2 = 0;

	while (i < 2)
	{
		len1 = _strlen(s);
		len2 = _strlen(bi[i].name);
		if (len1 == len2)
		{
			j = 0;
			while (s[j] != '\0')
			{
				if (s[j] == bi[i].name[j])
					j++;
				else
				{
					flag = 0;
					break;
				}
			}
			if (flag == 1)
				return (*(bi[i]).f);
		}
		i++;
	}
	return (NULL);
}

/**
 * env_ - function that prints the current environment on standard output
 * @array_buf: pointer to array of pointers to the args passed in by the user
 * on standard input
 * @buf: command line passed in by the user on standard input
 * @path_str: pointer to the PATH string
 * @array_path: pointer to array of pointers to the PATH directories
 * @exit_status: 0 if the previous command was found, -1 if the command was
 * not found
 * Return: void
 */

void env_(char **array_buf, char *buf, char *path_str, char **array_path,
	  int exit_status)
{
	int i = 0;

	(void)path_str;
	(void)array_path;
	(void)exit_status;
	for (i = 0; environ[i]; i++)
		_print(environ[i]), _print("\n");
	free(array_buf);
	free(buf);
}

/**
 * exit_ - function that exits the shell when called
 * @array_buf: pointer to array of pointers to the args passed in by the user
 * on standard input
 * @buf: command line passed in by the user on standard input
 * @path_str: pointer to the PATH string
 * @array_path: pointer to array of pointers to the PATH directories
 * @exit_status: 0 if the previous command was found, -1 if the command was
 * not found
 * Return: void
 */

void exit_(char **array_buf, char *buf, char *path_str, char **array_path,
	   int exit_status)
{
	free(path_str);
	free(array_path);
	free(array_buf);
	free(buf);
	exit(exit_status);
}
