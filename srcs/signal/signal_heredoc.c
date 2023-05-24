/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 19:33:39 by mqueguin          #+#    #+#             */
/*   Updated: 2022/02/24 04:02:43 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ignore_sig(int sig)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_IGN;
	sigaction(sig, &sa, NULL);
}

void	set_sig(void (*sig_handler)(int), int sig)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sa.sa_handler = sig_handler;
	sigaction(sig, &sa, NULL);
}

void	interrupt_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		exit(130);
	}
	else if (sig == SIGQUIT)
	{
		printf("\r");
		rl_on_new_line();
		rl_redisplay();
		printf(" ");
		printf("\r");
		rl_on_new_line();
		rl_redisplay();
	}
}
