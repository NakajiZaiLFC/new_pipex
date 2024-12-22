/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakajim <snakajim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:55:44 by snakajim          #+#    #+#             */
/*   Updated: 2024/12/22 16:56:08 by snakajim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(char **argv, int argc, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
		return (ft_putstr_fd("Error: Invalid number of arguments\n", 2), 1);
	if (!pipex_init(&pipex, argc, argv, envp))
		return (free_pipex(&pipex), err_msg(NULL), 1);
	if (!parse_input(&pipex))
		return (free_pipex(&pipex), 1);
	if (!create_pipes(&pipex))
		return (free_pipex(&pipex), err_msg(NULL), 1);
	if (!run_cmds(&pipex))
		return (free_pipex(&pipex), err_msg(NULL), 1);
	free_pipex(&pipex);
	return (pipex.exit_code);
}

bool	pipex_init(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->cmds = NULL;
	pipex->infile_fd = -1;
	pipex->outfile_fd = -1;
	pipex->exit_code = 0;
	pipex->paths = NULL;
	pipex->cmd_count = argc - 3;
	pipex->argv = argv;
	pipex->pipes = NULL;
	pipex->child_pids = NULL;
	pipex->paths = NULL;
	pipex->envp = envp;
	if (!cmds_init(pipex))
		return (false);
	return (true);
}

bool	cmds_init(t_pipex *pipex)
{
	size_t	i;

	i = 0;
	pipex->cmds = malloc(pipex->cmd_count * sizeof(t_cmd));
	if (!pipex->cmds)
		return (false);
	while (i < pipex->cmd_count)
	{
		pipex->cmds[i].found = false;
		pipex->cmds[i].path = NULL;
		pipex->cmds[i].args = NULL;
		i++;
	}
	return (true);
}
