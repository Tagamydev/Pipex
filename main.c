/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:43:05 by samusanc          #+#    #+#             */
/*   Updated: 2023/07/14 07:27:27 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <pipex.h>

//	gestion del input que el input exista, y que los argumentos existan
//	abrir el infile
//	abrir el outfile
//	crear el pipe
//	parseamos el path
//	hacemos el primer fork
//	ejecutamos el primer hijo
//		dup2 al pipe
//		cerramos el primer pipe
//		hacemos un dup2 al infile
//		obtenemos los argumentos del comando para el execv por medio de un split
//		obtenemos el comando
//		ejecutamos el commando antes asegurandonos que se pueda ejecutar
//	hacemos el segundo fork
//		hace lo mismo que el primer hijo
//	cerramos el pipe
//	esperamos a que el proceso 1 termine
//	esperamos a que el proceso 2 termine
//	terminamos la ejecucion

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		id;

	if (!envp)
		ft_error_log("QUE_TE_JODAN");
	if (argc != 5)
		ft_error_log("USE\nUsage: ./pipex infile command1 command2 outfile");
	pipex.paths = ft_get_paths(envp);
	id = pipe(pipex.pipe);
	if (id == -1)
		ft_error_log("PIPE_OPEN");
	pipex.pid1 = fork();
	if (!pipex.pid1)
		ft_first_child(&pipex, argv[1], argv[2]);
	pipex.pid2 = fork();
	if (!pipex.pid2)
		ft_second_child(&pipex, argv[4], argv[3]);
	close(pipex.pipe[1]);
	close(pipex.pipe[0]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return (0);
}
