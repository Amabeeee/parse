/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_in3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:49:23 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/14 19:12:56 by amdevezi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_multiple_middle_chevrons(int *i, const char *s)
{
	int	count;

	count = 0;
	while (s[*i] == '<')
	{
		count++;
		(*i)++;
	}
	if (count == 4)
		return (gest_error_token(BAD_TOK, "`<'\n", 2), 0);
	if (count == 5)
		return (gest_error_token(BAD_TOK, "`<<'\n", 2), 0);
	if (count >= 6)
		return (gest_error_token(BAD_TOK, "`<<<'\n", 2), 0);
	return (1);
}

static int	handle_extra_chevrons(const char *s, int i)
{
	int	chevron_count;
	int	j;

	chevron_count = 0;
	j = i;
	while (s[j] == '<')
	{
		chevron_count++;
		j++;
	}
	if (chevron_count == 1)
		return (gest_error_token(BAD_TOK, "`<'\n", 2), 0);
	if (chevron_count >= 2)
		return (gest_error_token(BAD_TOK, "`<<'\n", 2), 0);
	return (1);
}

int	check_multiple_heredoc_middle(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '<' && s[i + 1] == '<')
		{
			i = i + 2;
			while (s[i] && ft_isspace(s[i]))
				i++;
			if (s[i] == '<')
				return (handle_extra_chevrons(s, i));
		}
		else
			i++;
	}
	return (1);
}

int	handle_chevrons_after_end(int *i, const char *s)
{
	int	count;

	(*i)++;
	while (s[*i] && ft_isspace(s[*i]))
		(*i)++;
	if (s[*i] == '\0')
		return (gest_error_token(BAD_TOK, "`newline'\n", 2), 0);
	count = 0;
	while (s[*i] == '<')
	{
		count++;
		(*i)++;
	}
	if (multiple_heredoc_start_message(count) == 0)
		return (0);
	return (1);
}

int	check_multiple_heredoc_end(const char *s)
{
	int	i;

	i = ft_strlen(s) - 1;
	while (i >= 0 && ft_isspace(s[i]))
		i--;
	while (i >= 1)
	{
		if (s[i - 1] == '<' && s[i] == '<')
		{
			if (handle_chevrons_after_end(&i, s) == 0)
				return (0);
			break ;
		}
		i--;
	}
	return (1);
}
