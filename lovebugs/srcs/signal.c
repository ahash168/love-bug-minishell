/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 22:15:41 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/24 22:40:05 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	disable_ctrl_c_echo(void)
{
	struct termios	term;

	term = (struct termios){0};
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	catch_sig(t_sigaction *sa)
{
	sigaction(SIGINT, sa, NULL);
	sigaction(SIGQUIT, sa, NULL);
}

void	signals_handler(int sig, siginfo_t *siginfo, void *ptr)
{
	(void) ptr;
	(void) siginfo;
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_recived_signal = 1;
	}
}

void	mask_sig(t_sigaction *sa)
{
	sigemptyset(&sa->sa_mask);
	sigaddset(&sa->sa_mask, SIGINT);
	sigaddset(&sa->sa_mask, SIGQUIT);
}

void	init_sigaction(t_mini *shell)
{
	t_sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = &signals_handler;
	if (g_recived_signal == 1)
	{
		shell->exit_status = 1;
		g_recived_signal = 0;
	}
	sa.sa_flags = 0;
	sa.sa_flags = SA_SIGINFO;
	mask_sig(&sa);
	catch_sig(&sa);
}
