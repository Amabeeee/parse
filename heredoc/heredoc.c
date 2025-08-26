/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:56:33 by lauraper          #+#    #+#             */
/*   Updated: 2025/08/20 22:17:45 by lauraper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc(char *delimiter, t_env **envp)
{
	char	*cleaned;
	int		ret;

	if (is_in(delimiter, '\'') || is_in(delimiter, '\"'))
	{
		cleaned = delete_quote(delimiter);
		if (!cleaned)
			return (-1);
		ret = read_heredoc(cleaned, NULL);
		free(cleaned);
		return (ret);
	}
	else
		return (read_heredoc(delimiter, envp));
	return (0);
}

void	write_expanded(t_env **envp, char *res, int fd)
{
	char	*expanded;

	expanded = expand_re(envp, res);
	write(fd, expanded, ft_strlen((const char *)expanded));
	free(expanded);
	close(fd);
}

void	write_here(char *res, int *ft_pipe, t_env **envp)
{
	if (envp)
		write_expanded(envp, res, ft_pipe[1]);
	else
		write(ft_pipe[1], res, ft_strlen((const char *)res));
	close(ft_pipe[1]);
}

int	check_exit_status(int *ft_pipe)
{
	if (WIFEXITED(g_last_return) && WEXITSTATUS(g_last_return) == 130)
	{
		g_last_return = 130;
		close(ft_pipe[0]);
		return (-2);
	}
	return (0);
}
