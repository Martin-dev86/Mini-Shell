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

//void setup_signals(t_son *son)
//{
//    struct sigaction sa;
//
//    sa.sa_handler = (void (*)(int))sigint_handler;
//    sigemptyset(&sa.sa_mask);
//    sa.sa_flags = 0;
//    sigaction(SIGINT, &sa, NULL);
//}

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

void sigint_handler(int signo, t_son *son)
{
    (void)signo;
    write(STDOUT_FILENO, "\n", 1); 
    rl_replace_line("", 0);         // Limpiar la línea de readline
    rl_on_new_line();               // Mover el cursor a la nueva línea
    rl_redisplay();                 // Redibujar el prompt       // Indica que se ha interrumpido
}