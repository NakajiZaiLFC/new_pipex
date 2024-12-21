
#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_cmd
{
	bool	found;
	char	*path;
	char	**args;
}	t_cmd;


typedef struct s_pipex
{
	int infile_fd;
	int outfile_fd;
	int exit_code;
	char **paths;
	int cmd_count;
	char **argv;
	int **pipes;
	int *child_pids;
	t_cmd *cmds;
}	t_pipex;

#endif