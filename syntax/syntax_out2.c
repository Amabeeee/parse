/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_out2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:49:23 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/19 16:34:57 by amdevezi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_append_error_suffix(const char *s, int j)
{
	int	chevron_count;

	chevron_count = 0;
	while (s[j] && ft_isspace(s[j]))
		j++;
	if (s[j] == '\0')
		return (gest_error_token(BAD_TOK, "`newline'\n", 2), 0);
	while (s[j] == '>')
	{
		chevron_count++;
		j++;
	}
	if (chevron_count >= 2)
		return (gest_error_token(BAD_TOK, "`>>'\n", 2), 0);
	else if (chevron_count == 1)
		return (gest_error_token(BAD_TOK, "`>'\n", 2), 0);
	if (s[j] == '<')
		return (gest_error_token(BAD_TOK, "`<'\n", 2), 0);
	return (1);
}

int	manage_append_start(const char *s)
{
	int	i;

	i = 0;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] != '>' || s[i + 1] != '>')
		return (0);
	i += 2;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '\0')
		return (gest_error_token(BAD_TOK, "`newline'\n", 2), 0);
	if (s[i] == '>' && s[i + 1] == '>')
		return (gest_error_token(BAD_TOK, "`>>'\n", 2), 0);
	if (s[i] == '>')
		return (gest_error_token(BAD_TOK, "`>'\n", 2), 0);
	if (s[i] == '|')
		return (gest_error_token(BAD_TOK, "`|'\n", 2), 0);
	if (s[i] == '<' && s[i + 1] == '<')
		return (gest_error_token(BAD_TOK, "`<<'\n", 2), 0);
	if (s[i] == '<')
		return (gest_error_token(BAD_TOK, "`<'\n", 2), 0);
	return (1);
}

int	handle_append_errors(const char *s, int i)
{
	if (s[i] == '\0')
		return (gest_error_token(BAD_TOK, "`newline'\n", 2), 0);
	if (s[i] == '>' && s[i + 1] != '>')
		return (gest_error_token(BAD_TOK, "`>'\n", 2), 0);
	if (s[i] == '>' && s[i + 1] == '>')
		return (gest_error_token(BAD_TOK, "`>>'\n", 2), 0);
	if (s[i] == '<' && s[i + 1] == '<' && s[i + 2] == '<')
		return (gest_error_token(BAD_TOK, "`<<<'\n", 2), 0);
	if (s[i] == '<' && s[i + 1] == '<')
		return (gest_error_token(BAD_TOK, "`<<'\n", 2), 0);
	if (s[i] == '<' && s[i + 1] == ' ')
		return (gest_error_token(BAD_TOK, "`<'\n", 2), 0);
	if (s[i] == '|')
		return (gest_error_token(BAD_TOK, "`|'\n", 2), 0);
	return (1);
}

int	check_append_middle_error(const char *s)
{
	int	i;

	i = 0;
	i = skip_spaces(s, i);
	while (s[i] && !ft_isspace(s[i]))
		i++;
	while (s[i])
	{
		i = skip_spaces(s, i);
		if (s[i] == '>' && s[i + 1] == '>')
		{
			i = i + 2;
			i = skip_spaces(s, i);
			if (handle_append_errors(s, i) == 0)
				return (0);
		}
		else if (s[i])
			i++;
	}
	return (1);
}

int	manage_append_end(const char *s)
{
	int	i;

	i = 0;
	while (ft_isspace(s[i]))
		i++;
	while (s[i])
	{
		if (s[i] == '>' && s[i + 1] == '>')
		{
			i = i + 2;
			while (ft_isspace(s[i]))
				i++;
			if (handle_append_errors(s, i) == 0)
				return (0);
		}
		i++;
	}
	return (1);
}
