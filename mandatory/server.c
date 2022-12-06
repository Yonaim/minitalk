/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:07:17 by yeonhkim          #+#    #+#             */
/*   Updated: 2022/12/06 23:46:32 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

struct s_client	g_client;

static void	exit_by_error(int errcode)
{
	char	*errmsg;
	char	*hintmsg;

	errmsg = "";
	hintmsg = NULL;
	if (errcode == ERR_INTERFERENCE_SIGNAL)
		errmsg = "Signal sent by a process not the client";
	else if (errcode == ERR_HASTY_CLIENT)
	{
		errmsg = "Extra signal while server catching previous one";
		hintmsg = "Use correct client program.";
	}
	ft_printf(RED "\n\nError: %s (error code: %#04x)\n", errmsg, errcode);
	if (hintmsg)
		ft_printf(RESET FAINT "Hint: %s\n", hintmsg);
	write(1, "\n", 1);
	if (g_client.exist)
		kill(g_client.pid, SIG_NACK);
	exit(EXIT_FAILURE);
}

static void	display(void)
{
	if (g_client.exist)
	{
		ft_printf(YELLO "\nNew connection established", g_client.pid);
		ft_putstr_fd("\n\n", 1);
		ft_putstr_fd(CYAN "-------------", 1);
		ft_printf(" Message from PID %05d ", g_client.pid);
		ft_putstr_fd("-------------", 1);
		ft_putstr_fd("\n\n", 1);
		ft_putstr_fd("=> " RESET, 1);
	}
	else
	{
		ft_putstr_fd("\n\n" CYAN, 1);
		ft_putstr_fd("--------------------------------------------------", 1);
		ft_putstr_fd("\n\n", 1);
		ft_putstr_fd(GREEN "RECEIVING SUCCESS\n\n" RESET, 1);
	}
}

static void	receive_message(int sig)
{
	static struct s_msgbuff	msg;
	static struct s_bitbuff	bit;

	bit.buf = (bit.buf << 1) | (sig == SIG_ON_BIT);
	bit.cnt++;
	if (bit.cnt == 8)
	{
		msg.buf[msg.cnt++] = bit.buf;
		if (bit.buf == '\0' || msg.cnt == sizeof(msg.buf))
		{
			write(1, msg.buf, msg.cnt);
			msg.cnt = 0;
			if (bit.buf == '\0')
			{
				g_client.exist = false;
				display();
			}
		}
		bit.cnt = 0;
	}
}

static void	handler(int sig, siginfo_t *s_info, void *context)
{
	static volatile sig_atomic_t	catching;

	(void)context;
	if (!g_client.exist)
	{
		g_client.pid = s_info->si_pid;
		g_client.exist = true;
		display();
	}
	if (s_info->si_pid != g_client.pid)
	{
		kill(s_info->si_pid, SIG_NACK);
		exit_by_error(ERR_INTERFERENCE_SIGNAL);
	}
	else if (catching == 1)
		exit_by_error(ERR_HASTY_CLIENT);
	catching = 1;
	receive_message(sig);
	catching = 0;
	if (kill(g_client.pid, SIG_ACK) < 0)
	{
		ft_printf(RED "\n\nCannot connect to client\n");
		g_client.exist = false;
	}
}

int	main(void)
{
	print_program_name("server");
	ft_putstr_fd("\n=================================================\n", 1);
	ft_printf(BOLD "\t\tserver PID: %d\n", getpid());
	ft_putstr_fd(YELLO "(The client must taken this PID as parameter)\n", 1);
	ft_putstr_fd(RESET "=================================================", 1);
	ft_putstr_fd("\n\n", 1);
	init_sigaction(handler);
	while (1)
	{
		if (!g_client.exist)
			printf(RESET "Waiting new client...\n");
		sleep(5);
	}
}
