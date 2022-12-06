/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yona <yona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 00:48:15 by yeonhkim          #+#    #+#             */
/*   Updated: 2022/12/06 04:08:20 by yona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	init_sigaction(void *handler)
{
	struct sigaction	act;

	act.sa_sigaction = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = (SA_SIGINFO | SA_RESTART | SA_NODEFER);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
}

void	print_program_name(char *role)
{
	ft_putstr_fd(CYAN, 1);
	ft_putstr_fd("           _       _ _        _ _    \n", 1);
	ft_putstr_fd(" _ __ ___ (_)_ __ (_) |_ __ _| | | __\n", 1);
	ft_putstr_fd("| '_ ` _ \\| | '_ \\| | __/ _` | | |/ /\n", 1);
	ft_putstr_fd("| | | | | | | | | | | || (_| | |   < \n", 1);
	ft_putstr_fd("|_| |_| |_|_|_| |_|_|\\__\\__,_|_|_|\\_\\", 1);
	ft_putstr_fd(RESET, 1);
	ft_printf(" - %s -\n", role);
}
