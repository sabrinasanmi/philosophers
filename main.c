/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabsanto <sabsanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:21:05 by sabsanto          #+#    #+#             */
/*   Updated: 2025/05/15 20:35:22 by sabsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		result;

	if (argc < 5 || argc > 6)
	{
		printf("Erro: número inválido de argumentos.\n");
		return (1);
	}
	result = init_data(&data, argc, argv);
	if (result != 0)
	{
		printf("Erro na inicialização dos dados.\n");
		return (1);
	}
	// Aqui você irá chamar a função para criar as threads dos filósofos
	// e começar a simulação no passo seguinte.
	return (0);
}
