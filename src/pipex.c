/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakajim <snakajim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 14:02:30 by snakajim          #+#    #+#             */
/*   Updated: 2024/12/22 14:37:11 by snakajim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

bool	create_pipes(t_pipex *pipex)
{
	size_t	i;

	i = 0;
	pipex->pipes = malloc((pipex->cmd_count - 1) * sizeof(int *));
	if (!pipex->pipes)
		return (false);
	while (i < pipex->cmd_count - 1)
	{
		pipex->pipes[i] = malloc(2 * sizeof(int));
		if (!pipex->pipes[i])
			return (false);
		if (pipe(pipex->pipes[i]) == -1)
			return (false);
		i++;
	}
	return (true);
}

bool	run_cmds(t_pipex *pipex)
{
	int		pid;
	size_t	i;

	if (!allocate_pids(pipex))
		return (false);
	i = 0;
	while (i < pipex->cmd_count)
	{
		pid = fork();
		if (pid == 0)
			children(*pipex, i);
		else if (pid > 0)
			pipex->child_pids[i] = pid;
		else
			return (close_all_fds(pipex), false);
		i++;
	}
	close_all_fds(pipex);
	wait_pids(pipex);
	return (true);
}

bool	allocate_pids(t_pipex *pipex)
{
	size_t	i;

	pipex->child_pids = malloc(pipex->cmd_count * sizeof(int));
	if (!pipex->child_pids)
		return (false);
	i = 0;
	while (i < pipex->cmd_count)
	{
		pipex->child_pids[i] = -1;
		i++;
	}
	return (true);
}

void	wait_pids(t_pipex *pipex)
{
	size_t i;

	i = 0;
	while (i < pipex->cmd_count && pipex->child_pids[i] > 0)
	{
		waitpid(pipex->child_pids[i], NULL, 0);
		i++;
	}
	if (pipex->outfile_fd == -1)
		pipex->exit_code = 1;
	else if (!pipex->cmds[pipex->cmd_count - 1].found)
		pipex->exit_code = 127;
	else
		pipex->exit_code = 0;
}