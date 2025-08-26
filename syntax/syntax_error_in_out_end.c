/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_in_out_end.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:29:31 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/15 14:24:24 by amdevezi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_prev_chevron_diff(const char *s, int pos, char c)
{
	int	i;

	i = pos - 1;
	while (i >= 0 && (s[i] == ' ' || s[i] == '\t'))
		i--;
	if (i >= 0 && (s[i] == '<' || s[i] == '>') && s[i] != c)
		return (1);
	return (0);
}

static int	handle_chevron_end_followup(const char *s, int pos, int count)
{
	if (count != 1)
		return (1);
	while (s[pos] == ' ' || s[pos] == '\t')
		pos++;
	if (s[pos] == '\0')
		return (gest_error_token(BAD_TOK, "`newline'\n", 2), 0);
	if (s[pos] == '<')
		return (gest_error_token(BAD_TOK, "`<'\n", 2), 0);
	if (s[pos] == '>')
		return (gest_error_token(BAD_TOK, "`>'\n", 2), 0);
	return (1);
}

static int	handle_prev_chevron_seq(char chevron, int count)
{
	if (chevron == '<')
	{
		if (count >= 3)
			return (gest_error_token(BAD_TOK, "`<<<'\n", 2), 0);
		if (count == 2)
			return (gest_error_token(BAD_TOK, "`<<'\n", 2), 0);
		return (gest_error_token(BAD_TOK, "`<'\n", 2), 0);
	}
	return (gest_error_token(BAD_TOK, "`>>'\n", 2), 0);
}

static int	handle_diff_prev_chevron(char chevron)
{
	if (chevron == '<')
		return (gest_error_token(BAD_TOK, "`<'\n", 2), 0);
	if (chevron == '>')
		return (gest_error_token(BAD_TOK, "`newline'\n", 2), 0);
	return (handle_single_or_spaced_chevron(chevron));
}

int	check_out_in_end_error(const char *s)
{
	int		end;
	int		count;
	int		j;
	char	chevron;
	int		pos;

	end = find_last_non_space_chevron(s);
	if (end == -1)
		return (1);
	if (ft_strncmp(s, "<>", 2) == 0)
		return (gest_error_token(BAD_TOK, "`newline'\n", 2), 0);
	chevron = s[end];
	count = count_consecutive_chevrons(s, end, chevron);
	j = end - count;
	if (has_previous_chevron_sequence(s, j, chevron))
		return (handle_prev_chevron_seq(chevron, count));
	if (count == 1 && is_prev_chevron_diff(s, end, chevron))
		return (handle_diff_prev_chevron(chevron));
	pos = end + 1;
	return (handle_chevron_end_followup(s, pos, count));
}
