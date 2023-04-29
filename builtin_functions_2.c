#include "sample.h"
/**
 * my_cd - change directory
 * @args: parsed command
 *
 * Return: 0 or 1
 */
int my_cd(char **args)
{
if (args[1] == NULL)
{
chdir(getenv("HOME"));
}
else
{
if (chdir(args[1]) != 0)
{
printf("%s\n", args[1]);
perror("./shell: No such file or directory\n");
}
}
return (1);
}

/**
 * my_exit - exit shell
 * @argv: integer arg of exit
 *
 * Return: 1
 */
int my_exit(char **argv)
{
	if (!argv[1])
		exit(EXIT_SUCCESS);
	else
	{
		if (atoi(argv[1]))
			setenv("$?", argv[1], 1);
		else
			setenv("$?", "2", 1);
		exit(EXIT_FAILURE);
	}
return (1);
}
/**
 * loop - loop func
 * @envp: environment of shell
 *
 * Return: void
 */
void loop(char **envp)
{
char *line;
char **args;
int status;

do {
line = read_line();
args = split_line(line);
status = execute(args, envp);
free(line);
free(args);
} while (status);
}
/**
 * split_line - read command
 * @line: input
 *
 * Return: 1 or launch funnc output
 */
char **split_line(char *line)
{
int bufsize = BUFSIZE, position = 0;
char *token, **tokens_backup;
char **tokens = malloc(bufsize * sizeof(char *));

if (!tokens)
{
fprintf(stderr, "allocation error\n");
exit(EXIT_FAILURE);
}
token = strtok(line, DELIM);
while (token != NULL)
{
tokens[position] = token;
position++;
if (position >= bufsize)
{
bufsize += BUFSIZE;
tokens_backup = tokens;
tokens = realloc(tokens, bufsize *sizeof(char *));
if (!tokens)
{
free(tokens_backup);
fprintf(stderr, "allocation error\n");
exit(EXIT_FAILURE);
}
}
token = strtok(NULL, DELIM);
}
tokens[position] = NULL;
return (tokens);
}
/**
 * launch - launch shell
 * @args: input of shell
 * @envp: environment of shell
 *
 * Return: 1
 */
int launch(char **args, char **envp)
{
pid_t pid;
int status;
char * const *env = envp;

pid = fork();
if (pid == 0)
{
execve(args[0], args, env);
if (execvp(args[0], args) == -1)
{
perror("Error in Launching.");
}
exit(EXIT_FAILURE);
}
else if (pid < 0)
{
perror("komal");
}
else
{
do {
waitpid(pid, &status, WUNTRACED);
} while (!WIFEXITED(status) && !WIFSIGNALED(status));
}
return (1);
}
