/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:07:13 by yeonhkim          #+#    #+#             */
/*   Updated: 2022/12/06 23:50:14 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

struct s_server	g_server;

static void	exit_by_error(unsigned int errcode)
{
	char	*errmsg;
	char	*hintmsg;

	errmsg = "";
	hintmsg = NULL;
	if (errcode == ERR_INVALID_SERVER_PID)
		errmsg = "Invalid server PID";
	else if (errcode == ERR_SERVER_STOPPED)
		errmsg = "There was a problem with the server and sending stopped";
	else if (errcode == ERR_HASTY_SERVER)
	{
		errmsg = "Extra signal while client catching previous one";
		hintmsg = "Use correct server program.";
	}
	ft_printf(RED "\nError: %s (error code: %#04x)\n", errmsg, errcode);
	if (hintmsg)
		ft_printf(RESET FAINT "Hint: %s\n", hintmsg);
	write(1, "\n", 1);
	exit(EXIT_FAILURE);
}

static void	send_bit(int sig)
{
	g_server.catching = true;
	if (kill(g_server.pid, sig) < 0)
		exit_by_error(ERR_INVALID_SERVER_PID);
	else if (!g_server.connected)
	{
		ft_putstr_fd(YELLO "Connection established" RESET "\n", 1);
		g_server.connected = 1;
	}
}

static void	send_byte(int byte)
{
	int	mask;
	int	sig;

	mask = 0x80;
	while (mask > 0)
	{
		if (byte & mask)
			sig = SIG_ON_BIT;
		else
			sig = SIG_OFF_BIT;
		send_bit(sig);
		while (g_server.catching)
			;
		mask >>= 1;
	}
}

static void	handler(int sig, siginfo_t *s_info, void *context)
{
	static volatile sig_atomic_t	catching;
	
	(void)context;
	if (s_info->si_pid != g_server.pid)
		return ;
	else if (catching == 1)
		exit_by_error(ERR_HASTY_SERVER);
	catching = 1;
	if (sig == SIG_NACK)
		exit_by_error(ERR_SERVER_STOPPED);
	g_server.catching = false;
	catching = 0;
}

int	main(int argc, char *argv[])
{
	char	*msg;

	if (argc != 3)
	{
		ft_putstr_fd("\nusage: " BOLD "client <server PID> <message>\n\n", 2);
		exit(1);
	}
	init_sigaction(handler);
	g_server.pid = ft_atoi(argv[1]);
	msg = argv[2];
	print_program_name("client");
	ft_putstr_fd("\nAttempting to connect to server... \n", 1);
	while (*msg)
		send_byte(*msg++);
	send_byte('\0');
	ft_putstr_fd(GREEN "\nSENDING SUCCESS\n\n" RESET, 1);
	return (0);
}
