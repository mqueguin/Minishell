/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:47:27 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/28 16:46:18 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	interruption_signal(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \b\b", 0);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	change_status("1");
}

void	quit_signal(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \b\b", 0);
}

int	handle_signal(void)
{
	if (signal(SIGINT, interruption_signal) < 0)
		return (0);
	if (signal(SIGQUIT, quit_signal) < 0)
		return (0);
	return (1);
}

void	sig_ignore(int sig)
{
	(void)sig;
	if (sig == SIGINT)
		ft_putstr_fd("\n", 1);
}

int	disable_signal(int pid)
{
	if (pid == 0)
	{
		if (signal(SIGINT, SIG_DFL) < 0)
			return (0);
		if (signal(SIGQUIT, SIG_DFL) < 0)
			return (0);
	}
	else
	{
		if (signal(SIGINT, sig_ignore) < 0)
			return (0);
		if (signal(SIGQUIT, sig_ignore) < 0)
			return (0);
	}
	return (1);
}
