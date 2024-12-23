/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassy <nassy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:41:33 by snakajim          #+#    #+#             */
/*   Updated: 2024/12/23 14:32:45 by nassy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	err_msg(char *file)
{
	char	*msg;

	ft_putstr_fd("pipex: ", 2);
	if (file)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
	}
	msg = ft_strdup(strerror(errno));
	if (msg)
		ft_putstr_fd(msg, 2);
	else
		ft_putstr_fd("error allocating err_msg", 2);
	ft_putstr_fd("\n", 2);
	if (msg)
		free(msg);
}

void	cmd_not_found(t_pipex *pipex, int i)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(pipex->cmds[i].args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	pipex->cmds[i].found = false;
}

void	no_such_command(t_pipex *pipex, size_t i)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(pipex->cmds[i].args[0], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	pipex->cmds[i].found = false;
}
