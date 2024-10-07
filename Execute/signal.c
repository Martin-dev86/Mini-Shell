/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:08:00 by cagarci2          #+#    #+#             */
/*   Updated: 2024/10/01 22:08:00 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_signals(void)
{
	struct	sigaction	sa;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);

	sa.sa_handler = sigquit_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

void	sigquit_handler(int signo)
{
	(void)signo;
	if (prompt_active == 1)
		write(STDOUT_FILENO, "Quit (core dumped)\n", 20);
}

void	sigint_handler(int signo)
{
	(void)signo;
	write(STDOUT_FILENO, "^C", 2);
	write(STDOUT_FILENO, "\nMinishell>", 12);
}