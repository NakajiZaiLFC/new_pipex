/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakajim <snakajim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:03:56 by snakajim          #+#    #+#             */
/*   Updated: 2024/12/22 17:48:12 by snakajim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*ft_strjoin_3(char *s1, char *s2, char *s3)
{
	char	*join1;
	char	*join2;

	join1 = ft_strjoin(s1, s2);
	join2 = ft_strjoin(join1, s3);
	free(join1);
	return (join2);
}
