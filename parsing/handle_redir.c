/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:49:23 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/14 18:23:43 by lauraper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_redirection(t_cmd *cmd, char **tokens, int i, t_env **envp)
{
	char	*t;

	t = tokens[i];
	if (!tokens[i + 1])
		return (i + 1);
	if (!ft_strcmp(t, "<"))
		handle_input_redirection(cmd, tokens[i + 1]);
	else if (!ft_strcmp(t, ">"))
		handle_output_redirection(cmd, tokens[i + 1]);
	else if (!ft_strcmp(t, ">>"))
		handle_output_append(cmd, tokens[i + 1]);
	else if (!ft_strcmp(t, "<<"))
		handle_heredoc(cmd, tokens[i + 1], envp);
	return (i + 2);
}

void	handle_input_redirection(t_cmd *cmd, char *filename)
{
	if (cmd->in != 0)
		close(cmd->in);
	cmd->in = open_infile(cmd, filename);
}

void	handle_output_redirection(t_cmd *cmd, char *filename)
{
	if (cmd->out != 1)
		close(cmd->out);
	cmd->out = open_outfile(cmd, filename);
}

void	handle_output_append(t_cmd *cmd, char *filename)
{
	if (cmd->out != 1)
		close(cmd->out);
	cmd->out = open_outfile_append(cmd, filename);
}

void	handle_heredoc(t_cmd *cmd, char *delimiter, t_env **envp)
{
	int	fd;

	if (cmd->in != 0)
		close(cmd->in);
	fd = heredoc(delimiter, envp);
	cmd->in = fd;
}
