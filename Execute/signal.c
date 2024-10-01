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

#include <signal.h>
#include "minishell.h"

void sigquit_handler(int signo)
{
    (void)signo;
        write(STDOUT_FILENO, "\nMinishell> ", 12);
}

void sigint_handler(int signo)
{
    (void)signo;
    write(STDOUT_FILENO, "\nMinishell> ", 12);
}