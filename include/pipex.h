/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassy <nassy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:46:50 by snakajim          #+#    #+#             */
/*   Updated: 2024/12/23 14:20:16 by nassy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_cmd
{
	bool	found;
	char	*path;
	char	**args;
}			t_cmd;

typedef struct s_pipex
{
	int		infile_fd;
	int		outfile_fd;
	int		exit_code;
	char	**paths;
	size_t	cmd_count;
	char	**argv;
	int		**pipes;
	int		*child_pids;
	char	**envp;
	t_cmd	*cmds;
}			t_pipex;

void		children(t_pipex *pipex, size_t i);
void		err_msg(char *file);
void		cmd_not_found(t_pipex *pipex, int i);
void		no_such_command(t_pipex *pipex, size_t i);
void		free_pipex(t_pipex *pipex);
void		close_all_fds(t_pipex *pipex);
bool		pipex_init(t_pipex *pipex, int argc, char **argv, char **envp);
bool		parse_input(t_pipex *pipex);
bool		create_pipes(t_pipex *pipex);
bool		run_cmds(t_pipex *pipex);
char		*ft_strjoin_3(char *s1, char *s2, char *s3);

#endif