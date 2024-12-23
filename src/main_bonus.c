/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassy <nassy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:55:44 by snakajim          #+#    #+#             */
/*   Updated: 2024/12/23 14:10:48 by nassy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
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
