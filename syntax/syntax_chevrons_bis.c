/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_chevrons_bis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:49:23 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/10 09:32:19 by lauraper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_append_chevron_sequence(const char *s, int i)
{
	int	block_count;
	int	j;

	block_count = 0;
	j = i;
	while (s[j])
	{
		j = skip_spaces(s, j);
		if (s[j] == '>' && s[j + 1] == '>')
		{
			block_count++;
			j += 2;
		}
		else
			break ;
	}
	if (block_count > 1)
		return (gest_error_token(BAD_TOK, "`>>'\n", 2), 0);
	j = skip_spaces(s, j);
	if (check_append_chevron_message(s[j]) == 0)
		return (0);
	return (1);
}

int	check_append_chevron_message(char c)
{
	if (c == '\0')
		return (gest_error_token(BAD_TOK, "`newline'\n", 2), 0);
	if (c == '>')
		return (gest_error_token(BAD_TOK, "`>'\n", 2), 0);
	if (c == '<')
		return (gest_error_token(BAD_TOK, "`<'\n", 2), 0);
	return (1);
}

int	handle_single_or_spaced_chevron(char chevron)
{
	if (chevron == '<')
		return (gest_error_token(BAD_TOK, "`<'\n", 2), 0);
	return (gest_error_token(BAD_TOK, "`>'\n", 2), 0);
}

int	check_chevron_error(const char *s, int j, char chevron)
{
	int	count;

	count = count_chevrons(s, j, chevron);
	return (report_chevron_error(count, chevron));
}
