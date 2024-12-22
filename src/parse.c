/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakajim <snakajim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:13:06 by snakajim          #+#    #+#             */
/*   Updated: 2024/12/22 19:10:27 by snakajim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

bool	parse_input(t_pipex *pipex)
{
	size_t	i;

	find_paths(pipex);
	open_files(pipex);
	i = 0;
	while (i < pipex->cmd_count)
	{
		pipex->cmds[i].args = ft_split(pipex->argv[i + 2], ' ');
		if (!pipex->cmds[i].args)
			return (false);
		if (!(i == 0 && pipex->infile_fd == -1) && !(i == pipex->cmd_count - 1
				&& pipex->outfile_fd == -1))
			find_command(pipex, i);
		i++;
	}
	return (true);
}

void	find_paths(t_pipex *pipex)
{
	size_t	i;

	i = 0;
	if (!pipex->envp)
		return ;
	while (pipex->envp[i] && ft_strncmp(pipex->envp[i], "PATH", 4))
		i++;
	if (pipex->envp[i] && ft_strncmp(pipex->envp[i], "PATH", 4) == 0)
		pipex->paths = ft_split(pipex->envp[i] + 5, ':');
}

void	open_files(t_pipex *pipex)
{
	pipex->infile_fd = open(pipex->argv[1], O_RDONLY);
	if (pipex->infile_fd == -1)
	{
		if (access(pipex->argv[1], F_OK) != 0)
			err_msg(pipex->argv[1]);
		else if (access(pipex->argv[1], R_OK) != 0)
			err_msg(pipex->argv[1]);
		else
			ft_putstr_fd("Erorr: infile undefined\n", 2);
	}
	pipex->outfile_fd = open(pipex->argv[pipex->cmd_count + 2],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile_fd == -1)
	{
		if (access(pipex->argv[pipex->cmd_count + 2], W_OK) != 0)
			err_msg(pipex->argv[pipex->cmd_count + 2]);
		else
			ft_putstr_fd("Error: outfile undefined\n", 2);
	}
}

void	find_command(t_pipex *pipex, size_t i)
{
	char	*cmd;
	size_t	j;

	if (pipex->cmds[i].args[0] && is_command(pipex,
			ft_strdup(pipex->cmds[i].args[0]), i))
		return ;
	j = 0;
	if (!pipex->paths)
		return (no_such_command(pipex, i));
	while (pipex->paths[j])
	{
		cmd = ft_strjoin_3(pipex->paths[j], "/", pipex->cmds[i].args[0]);
		if (is_command(pipex, cmd, i))
			break ;
		if (!pipex->paths[++j])
			cmd_not_found(pipex, i);
	}
}

bool	is_command(t_pipex *pipex, char *cmd, size_t i)
{
	if (!cmd)
		return (false);
	if (access(cmd, F_OK) == 0 && ft_strncmp(cmd, "/", 1) == 0)
	{
		pipex->cmds[i].path = ft_strdup(cmd);
		if (!pipex->cmds[i].path)
			return (free(cmd), false);
		free(cmd);
		pipex->cmds[i].found = true;
		return (true);
	}
	free(cmd);
	return (false);
}
