/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:50:26 by samusanc          #+#    #+#             */
/*   Updated: 2023/07/14 03:41:31 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_ERROR_H
# define FT_ERROR_H
# define ERROR_INVALID_MAP "INVALID_MAP\nMake sure the .fdf file has permissions"
# include <stdio.h>
# include <unistd.h>
# include <libft.h>

void		ft_error_log(char *str);
void		ft_pipex_error_log(char *file, char *error);

#endif
