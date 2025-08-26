/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:49:23 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/14 12:51:03 by amdevezi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pipe_error_start(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && ft_isspace(s[i]))
	{
		i++;
	}
	if ((s[i] == '|' && s[i + 1] == '\0'))
		return (gest_error_token(BAD_TOK, "`|'\n", 2), 0);
	else if (s[i] == '|' && s[i + 1] != '|')
		return (gest_error_token(BAD_TOK, "`|'\n", 2), 0);
	else if ((s[i] == '|') && ft_isspace(s[i]))
		return (gest_error_token(BAD_TOK, "`|'\n", 2), 0);
	else if (s[i] == '|' && s[i + 1] == '|')
		return (gest_error_token(BAD_TOK, "`||'\n", 2), 0);
	else if (s[i] == '|' && s[i + 1] == '|')
	{
		while (s[i] == '|')
			i++;
		return (gest_error_token(BAD_TOK, "`||'\n", 2), 0);
	}
	return (1);
}

int	check_pipe_error_middle(const char *s)
{
	int	i;
	int	pipe_count;

	i = 0;
	while (s[i])
	{
		if (s[i] == '|')
		{
			pipe_count = 1;
			i++;
			while (s[i] == '|')
			{
				pipe_count++;
				i++;
			}
			if (pipe_count == 3 || pipe_count == 2)
				return (gest_error_token(BAD_TOK, "'|'\n", 2), 0);
			else if (pipe_count > 3)
				return (gest_error_token(BAD_TOK, "'||'\n", 2), 0);
		}
		else
			i++;
	}
	return (1);
}

int	check_pipe_error_end(const char *s)
{
	int	i;
	int	pipe_found;

	i = ft_strlen(s) - 1;
	pipe_found = 0;
	while (i >= 0 && ft_isspace(s[i]))
		i--;
	while (i >= 0)
	{
		while (i >= 0 && ft_isspace(s[i]))
			i--;
		if (i >= 0 && s[i] == '|')
		{
			pipe_found++;
			i--;
		}
		else
			break ;
	}
	if (pipe_found > 1)
		return (gest_error_token(BAD_TOK, "`|'\n", 2), 0);
	return (1);
}
