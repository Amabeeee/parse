/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_in2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:49:23 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/19 19:44:40 by lauraper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_chevrons(int *i, const char *s)
{
	int	chevron_count;

	while (s[*i] && ft_isspace(s[*i]))
		(*i)++;
	chevron_count = 0;
	while (s[*i] == '<' && s[*i] != '\0')
	{
		chevron_count++;
		(*i)++;
	}
	if (chevron_count == 0)
		return (1);
	if (chevron_count == 2)
		return (1);
	if (multiple_heredoc_start_message(chevron_count) == 0)
		return (0);
	return (1);
}

int	check_is_safe(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] == '<' || s[i] == '>')
		return (1);
	if (is_operator(s[i]) || s[i] == '\0')
		return (0);
	return (1);
}

static int	skip_spaces_2(const char *s, int pos)
{
	while (s[pos] && ft_isspace(s[pos]))
		pos++;
	return (pos);
}

int	check_multiple_heredoc_start(const char *s)
{
	int	i;

	i = 0;
	i = skip_spaces_2(s, i);
	if (s[i] == '\0' || s[i + 1] == '\0' || !(s[i] == '<' && s[i + 1] == '<'))
		return (1);
	i = i + 2;
	i = skip_spaces_2(s, i);
	if (s[i] == '\0')
		return (gest_error_token(BAD_TOK, "`newline'\n", 2), 0);
	while (s[i])
	{
		if (handle_chevrons(&i, s) == 0)
		{
			if (s[i + 1] == '\0')
				break ;
			if (!check_is_safe(&s[i + 1]))
				return (0);
		}
		else if (s[i])
			i++;
	}
	return (1);
}
