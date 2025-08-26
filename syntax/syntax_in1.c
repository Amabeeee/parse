/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_in1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:05:20 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/19 13:47:11 by amdevezi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_single_heredoc_start(const char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	while (s[i] == '<')
	{
		count++;
		i++;
	}
	if (count == 2 || count == 3)
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i] == '\0')
			return (gest_error_token(BAD_TOK, "`newline'\n", 2), 0);
	}
	else if (single_heredoc_start_message(count) == 0)
		return (0);
	return (1);
}

int	handle_heredocs(int *i, const char *s)
{
	int	count;

	count = 2;
	*i = *i + 2;
	while (s[*i] && s[*i] == '<')
	{
		count++;
		(*i)++;
	}
	while (s[*i] && ft_isspace(s[*i]))
	{
		(*i)++;
	}
	if (count == 2 && s[*i] == '\0')
		return (gest_error_token(BAD_TOK, "`newline'\n", 2), 0);
	if (count == 3)
		return (gest_error_token(BAD_TOK, "`<'\n", 2), 0);
	if (single_heredoc_start_message(count) == 0)
		return (0);
	return (1);
}

int	is_multiple_heredoc_line(const char *s)
{
	int	i;
	int	heredoc_count;

	i = 0;
	heredoc_count = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i] == '<' && s[i + 1] == '<')
		{
			heredoc_count++;
			i = i + 2;
			while (s[i] == '<')
				i++;
		}
		else if (s[i])
			i++;
	}
	return (heredoc_count > 1);
}

int	parse_heredoc_line(const char *s)
{
	if (is_multiple_heredoc_line(s))
		return (check_multiple_heredoc_middle(s));
	else
		return (check_single_heredoc_middle(s));
}

int	check_single_heredoc_middle(const char *s)
{
	int	i;
	int	len;
	int	start;

	i = 0;
	while (s[i])
	{
		if (s[i] == '<')
		{
			start = i;
			while (s[i] == '<')
				i++;
			len = i - start;
			if (len > 2)
			{
				if (handle_heredocs(&start, s) == 0)
					return (0);
			}
		}
		else
		{
			i++;
		}
	}
	return (1);
}
