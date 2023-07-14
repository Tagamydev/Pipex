/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_log.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:01:37 by samusanc          #+#    #+#             */
/*   Updated: 2023/07/14 03:41:17 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <ft_error.h>

void	ft_error_log(char *str)
{
	write(2, "ERROR_", 6);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(-1);
}

void	ft_pipex_error_log(char *file, char *error)
{
	write(2, "pipex: ", 7);
	write(2, file, ft_strlen(file));
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	exit(-1);
}
