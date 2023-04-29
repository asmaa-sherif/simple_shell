#include "sample.h"
/**
 * main - main function
 * @argc: no. of arguments
 * @argv: arguments
 * @envp: environment of shell
 *
 * Return: 0
 */
int main(int argc, char **argv, char *envp[])
{
if (!argc)
printf("%d %s\n", argc, argv[0]);
loop(envp);
return (EXIT_SUCCESS);
}
