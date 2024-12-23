/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassy <nassy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:03:56 by snakajim          #+#    #+#             */
/*   Updated: 2024/12/23 14:24:23 by nassy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static bool	cmds_init(t_pipex *pipex);

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

static bool	cmds_init(t_pipex *pipex)
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

char	*ft_strjoin_3(char *s1, char *s2, char *s3)
{
	char	*join1;
	char	*join2;

	join1 = ft_strjoin(s1, s2);
	if (!join1)
		return (NULL);
	join2 = ft_strjoin(join1, s3);
	free(join1);
	return (join2);
}
