/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakajim <snakajim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:46:50 by snakajim          #+#    #+#             */
/*   Updated: 2024/12/22 16:58:44 by snakajim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

void		children(t_pipex *pipex, size_t i);
void		child(t_pipex *pipex, size_t i, int in_fd, int out_fd);
void		redirect(t_pipex *pipex, int in_fd, int out_fd);
void		err_msg(char *file);
void		cmd_not_found(t_pipex *pipex, size_t i);
void		no_such_command(t_pipex *pipex, size_t i);
void		free_pipex(t_pipex *pipex);
void		free_array(char **array);
void		close_all_fds(t_pipex *pipex);
bool		pipex_init(t_pipex *pipex, int argc, char **argv, char **envp);
bool		cmds_init(t_pipex *pipex);
bool		parse_input(t_pipex *pipex);
void		find_paths(t_pipex *pipex);
void		open_files(t_pipex *pipex);
void		find_command(t_pipex *pipex, size_t i);
bool		is_command(t_pipex *pipex, char *cmd, size_t i);
bool		create_pipes(t_pipex *pipex);
bool		run_cmds(t_pipex *pipex);
bool		allocate_pids(t_pipex *pipex);
void		wait_pids(t_pipex *pipex);

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
	int		cmd_count;
	char	**argv;
	int		**pipes;
	int		*child_pids;
	char	**envp;
	t_cmd	*cmds;
}			t_pipex;

#endif