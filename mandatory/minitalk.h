/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 15:10:45 by yeonhkim          #+#    #+#             */
/*   Updated: 2022/12/06 23:44:46 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

/*-------------- STANDARD HEADERS ---------------*/

# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

/*-------------- USER DEFINED HEADERS ------------*/

# include "libft.h"

/*----------- DEFINE MACRO CONSTANTS ------------*/

/* ANSI Escape codes defines print style */
# define RESET						"\x1B[0m"
# define BOLD						"\x1B[1m"
# define FAINT						"\x1B[2m"
# define ITAL						"\x1B[3m"
# define RED						"\x1B[31m"
# define GREEN						"\x1B[32m"
# define YELLO						"\x1B[33m"
# define BLUE						"\x1B[34m"
# define MAGENTA					"\x1B[35m"
# define CYAN						"\x1B[36m"

/* User defined signal for server */
# define SIG_ON_BIT					SIGUSR1		/* ON bit(1)*/
# define SIG_OFF_BIT				SIGUSR2		/* OFF bit(0) */

/* User defined signal for client */
# define SIG_ACK					SIGUSR1		/* Acknowledgement */
# define SIG_NACK					SIGUSR2		/* Negative Acknowledgemant */

/* Error code */
# define ERR_INVALID_SERVER_PID		0x01		/* Invalid server PID */
# define ERR_SERVER_STOPPED			0x02		/* Server encountered a problem and stopped */
# define ERR_INTERFERENCE_SIGNAL	0x03		/* Interference signal occurred */
# define ERR_HASTY_CLIENT			0x04		/* Extra signal from incorrect client */
# define ERR_HASTY_SERVER			0x05		/* Extra signal from incorrect server */

/*------------- STRUCT DECLARATIONS --------------*/

struct s_bitbuff {
	char					buf;
	unsigned int			cnt;
};

struct s_msgbuff {
	char					buf[1024];
	unsigned int			cnt;
};

struct s_server {
	pid_t					pid;
	int						connected;
	volatile sig_atomic_t	catching;
};

struct s_client {
	pid_t					pid;
	int						exist;
};

/*-------------- FUNCTION PROTOTYPES -------------*/

void	init_sigaction(void *handler);
void	print_program_name(char *role);

#endif
