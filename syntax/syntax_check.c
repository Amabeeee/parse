/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:49:23 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/15 14:28:09 by amdevezi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_start(const char *s)
{
	int	valid;
	int	i;

	valid = 1;
	i = 0;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '>' && s[i + 1] == '>')
	{
		if (!manage_append_start(s))
			return (0);
	}
	else if (!check_pipe_error_start(s) || !check_full_line_chevrons(s))
		return (0);
	else if (!check_in_start_error(s) || !check_out_start_error(s))
		return (0);
	else if (!check_out_in_start_error(s) || !check_multiple_appends_start(s))
		return (0);
	else if (!check_single_heredoc_start(s) || !check_multiple_heredoc_start(s))
		return (0);
	return (valid);
}

int	check_middle(const char *s)
{
	int	valid;

	valid = 1;
	if (ft_strncmp(s, ">>", 2) == 0)
	{
		if (!manage_append_end(s))
		{
			return (0);
		}
	}
	if (!check_pipe_error_middle(s))
		return (0);
	if (!check_in_middle_error(s))
		return (0);
	if (!check_out_middle_error(s))
		return (0);
	if (!check_append_middle_error(s))
		return (0);
	if (!check_multiple_appends_middle(s))
		return (0);
	if (!parse_heredoc_line(s))
		return (0);
	return (valid);
}

int	check_end(const char *s)
{
	int	valid;

	valid = 1;
	if (!check_pipe_error_end(s))
		return (0);
	else if (!check_multiple_heredoc_end(s))
	{
		return (0);
	}
	else if (!check_out_in_end_error(s))
	{
		return (0);
	}
	else if (!manage_append_end(s))
	{
		return (0);
	}
	else if (!check_multiple_appends_end(s))
	{
		return (0);
	}
	return (valid);
}

int	test_all(const char *s)
{
	if (!check_start(s))
		return (0);
	else if (!check_middle(s))
		return (0);
	else if (!check_end(s))
		return (0);
	else
		return (1);
}

int	check_full_line_chevrons(const char *s)
{
	int	i;
	int	chevron_count;

	i = 0;
	chevron_count = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	while (s[i] == '<')
	{
		chevron_count++;
		i++;
	}
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] == '\0')
	{
		if (full_line_chevron_message(chevron_count) == 0)
			return (0);
	}
	return (1);
}
