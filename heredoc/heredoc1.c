/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:09:22 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/20 07:22:32 by lauraper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_delimiter(char *line, char *delimiter)
{
	return (ft_strcmp(line, delimiter) == 0);
}

static void	print_eof_warning(int count, char *delimiter)
{
	printf("Minishell: warning: here-document at line ");
	printf("%d delimited by end-of-file ", count);
	printf("wanted `%s')\n", delimiter);
	g_last_return = 0;
}

static int	handle_line(char **res, char *line)
{
	*res = concate(*res, line);
	if (!res)
		return (-1);
	return (1);
}

static int	read_loop(char *delimiter, int *ft_pipe, t_env **envp, char **res)
{
	char	*line;
	int		count;

	count = 0;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			print_eof_warning(count, delimiter);
			break ;
		}
		if (is_delimiter(line, delimiter))
			break ;
		count = count + handle_line(res, line);
		free(line);
	}
	free(line);
	write_here(*(res), ft_pipe, envp);
	exit (1);
}

int	read_heredoc(char *delimiter, t_env **envp)
{
	pid_t	exe;
	int		ft_pipe[2];
	char	*res;

	res = malloc(1);
	if (!res)
		return (-2);
	res[0] = 0;
	pipe(ft_pipe);
	exe = fork();
	set_signal_ign();
	if (exe == 0)
	{
		set_signal_here();
		read_loop(delimiter, ft_pipe, envp, &res);
	}
	close(ft_pipe[1]);
	waitpid(exe, &g_last_return, 0);
	free(res);
	if (check_exit_status(ft_pipe) == -2)
		return (-2);
	return (ft_pipe[0]);
}
