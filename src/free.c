/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassy <nassy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 14:41:01 by snakajim          #+#    #+#             */
/*   Updated: 2024/12/23 14:23:38 by nassy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	free_array(char **array);

void	free_pipex(t_pipex *pipex)
{
	size_t	i;

	i = 0;
	while (i < pipex->cmd_count && pipex->cmds && pipex->cmds[i].args)
	{
		free_array(pipex->cmds[i].args);
		if (pipex->cmds[i].found)
			free(pipex->cmds[i].path);
		i++;
	}
	free(pipex->cmds);
	if (pipex->paths)
		free_array(pipex->paths);
	if (pipex->infile_fd != -1)
		close(pipex->infile_fd);
	if (pipex->outfile_fd != -1)
		close(pipex->outfile_fd);
	if (pipex->child_pids)
		free(pipex->child_pids);
}

static void	free_array(char **array)
{
	size_t	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	close_all_fds(t_pipex *pipex)
{
	size_t	i;

	i = 0;
	if (!pipex->pipes)
		return ;
	while (i < pipex->cmd_count - 1 && pipex->pipes[i])
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
		if (pipex->pipes[i])
			free(pipex->pipes[i]);
		i++;
	}
	free(pipex->pipes);
	if (pipex->infile_fd != -1)
		close(pipex->infile_fd);
	if (pipex->outfile_fd != -1)
		close(pipex->outfile_fd);
}
