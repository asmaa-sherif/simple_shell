#include "sample.h"

int (*built_in_function[]) (char **) = { &my_cd, &my_help, &my_exit};
/**
 * my_builtins - exit shell
 *
 * Return: size of builtin string
 */
int my_builtins(void)
{
char *built_in_string[] = {"cd", "help", "exit"};
return (sizeof(built_in_string) / sizeof(char *));
}
/**
 * my_help - help user
 * @args: command input
 *
 * Return: 0 or 1
 */
int my_help(char **args)
{
printf("This is simple C shell build by Komal Batool\n");
printf("Type program names and arguments, and hit enter.\n");
printf("%s is not a builtin function", args[0]);
printf("Use the man command for information on other programs.\n");
return (1);
}
/**
 * execute - shell execution
 * @args: input of shell
 * @envp: environment of shell
 *
 * Return: 1 or launch funnc output
 */
int execute(char **args, char **envp)
{
int i;
char *built_in_string[] = {"cd", "help", "exit"};

if (args[0] == NULL)
{
return (1);
}
for (i = 0; i < my_builtins(); i++)
{
if (strcmp(args[0], built_in_string[i]) == 0)
{
return ((*built_in_function[i])(args));
}
}
return (launch(args, envp));
}
/**
 * read_line - read command
 *
 * Return: input command
 */
char *read_line(void)
{
    #ifdef USE_STD_GETLINE
char *line = NULL;
ssize_t bufsize = 0;

if (getline(&line, &bufsize, stdin) == -1)
{
if (feof(stdin))
exit(EXIT_SUCCESS);
else
{
perror("can't read command.\n");
exit(EXIT_FAILURE);
}
}
return (line);
#else
int bufsize = RL_BUFSIZE;
int position = 0;
char *buffer = malloc(sizeof(char) * bufsize);
if (!buffer)
{
fprintf(stderr, "allocation error\n");
exit(EXIT_FAILURE);
}
while (1)
{
int c = getchar();
if (c == EOF)
exit(EXIT_SUCCESS);
else if (c == '\n')
{
buffer[position] = '\0';
return (buffer);
}
else
buffer[position] = c;
position++;
while_loop(buffer, position);
}
#endif
}
/**
 * while_loop - part of readline
 * @position: position
 * @buffer: buffer of input
 *
 * Return: void
 */
void while_loop(char *buffer, int position)
{
int bufsize = RL_BUFSIZE;
if (position >= bufsize)
{
bufsize += RL_BUFSIZE;
buffer = realloc(buffer, bufsize);
if (!buffer)
{
fprintf(stderr, "allocation error\n");
exit(EXIT_FAILURE);
}
}
}
