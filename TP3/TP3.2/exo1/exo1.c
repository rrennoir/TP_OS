#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);

char *builtin_str[] = {
  "cd",
  "help",
  "exit"
};

int (*builtin_func[]) (char **) = {
	&shell_cd,
	&shell_help,
	&shell_exit
};

int shell_num_builtins()
{
  	return sizeof(builtin_str) / sizeof(char *);
}

int shell_cd(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "MonShell: expected argument to \"cd\"\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("MonShell");
		}
	}
	return 1;
}

int shell_help(char **args)
{
	int i;
	printf("The following are built in:\n");

	for (i = 0; i < shell_num_builtins(); i++)
	{
		printf("  %s\n", builtin_str[i]);
	}
	return 1;
}

int shell_exit(char **args)
{
  	return 0;
}

int shell_launch(char **args)
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1) {
		perror("MonShell");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("MonShell");
	}
	else
	{
		while(!WIFEXITED(status) && !WIFSIGNALED(status))
		{
			wpid = waitpid(pid, &status, WUNTRACED);
		}
	}
    wait(0);
	return 1;
}

int shell_execute(char **args)
{
	int i;

	if (args[0] == NULL)
	{
		return 1;
	}
	for (i = 0; i < shell_num_builtins(); i++)
	{
		if (strcmp(args[0], builtin_str[i]) == 0)
		{
			return (*builtin_func[i])(args);
		}
	}
	return shell_launch(args);
}

char *shell_read_line(void)
{
	int bufsize = 1024;
	int position = 0;
	char *buffer = malloc(sizeof(char) * bufsize);
	int c;

	if (!buffer)
	{
		fprintf(stderr, "MonShell: allocation error\n");
		exit(EXIT_FAILURE);
	}
  	while (1)
  	{
		c = getchar();

		if (c == EOF || c == '\n')
		{
			buffer[position] = '\0';
			return buffer;
		}
		else
		{
			buffer[position] = c;
		}
		position++;

		if (position >= bufsize)
		{
			bufsize += 1024;
			buffer = realloc(buffer, bufsize);
			if (!buffer)
			{
				fprintf(stderr, "MonShell: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
  	}
}

char **shell_split_line(char *line)
{
	int bufsize = 64, position = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token;

  	if (!tokens)
	  {
		fprintf(stderr, "MonShell: allocation error\n");
    	exit(EXIT_FAILURE);
  	}

	token = strtok(line, " \t\r\n\a");
	while (token != NULL)
	{
		tokens[position] = token;
			position++;

		if (position >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!tokens) 
			{
				fprintf(stderr, "MonShell: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, " \t\r\n\a");
  	}
  	tokens[position] = NULL;
  	return tokens;
}

void main(void)
{
	char *line;
	char **args;
	int status;

	while(status)
	{
		printf("MonShell >>> ");
		line = shell_read_line();
		args = shell_split_line(line);
		status = shell_execute(args);
		
		free(line);
		free(args);
	}
}