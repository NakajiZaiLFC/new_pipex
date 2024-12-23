/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassy <nassy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 14:19:07 by snakajim          #+#    #+#             */
/*   Updated: 2024/12/23 14:23:59 by nassy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	child(t_pipex *pipex, size_t i, int in_fd, int out_fd);
static void	redirect(t_pipex *pipex, int in_fd, int out_fd);

void	children(t_pipex *pipex, size_t i)
{
	if (!pipex->cmds[i].found)
	{
		close_all_fds(pipex);
		free_pipex(pipex);
		exit(1);
	}
	if (i == 0)
		child(pipex, i, pipex->infile_fd, pipex->pipes[i][1]);
	else if (i != pipex->cmd_count - 1)
		child(pipex, i, pipex->pipes[i - 1][0], pipex->pipes[i][1]);
	else
		child(pipex, i, pipex->pipes[i - 1][0], pipex->outfile_fd);
}

static void	child(t_pipex *pipex, size_t i, int in_fd, int out_fd)
{
	redirect(pipex, in_fd, out_fd);
	close_all_fds(pipex);
	execve(pipex->cmds[i].path, pipex->cmds[i].args, pipex->envp);
	free_pipex(pipex);
	err_msg(NULL);
	exit(1);
}

static void	redirect(t_pipex *pipex, int in_fd, int out_fd)
{
	if (dup2(in_fd, STDIN_FILENO) == -1)
	{
		close_all_fds(pipex);
		free_pipex(pipex);
		exit(1);
	}
	close(in_fd);
	if (dup2(out_fd, STDOUT_FILENO) == -1)
	{
		close_all_fds(pipex);
		free_pipex(pipex);
		exit(1);
	}
	close(out_fd);
}
