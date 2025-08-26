/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_messages.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:49:23 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/14 17:58:47 by amdevezi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	full_line_chevron_message(int chevron_count)
{
	if (chevron_count == 1)
		return (gest_error_token(BAD_TOK, "`newline'\n", 2), 0);
	else if (chevron_count == 2 || chevron_count == 3)
		return (gest_error_token(BAD_TOK, "`newline'\n", 2), 0);
	else if (chevron_count == 4)
		return (gest_error_token(BAD_TOK, "`<'\n", 2), 0);
	else if (chevron_count == 5)
		return (gest_error_token(BAD_TOK, "`<<'\n", 2), 0);
	else if (chevron_count >= 6)
		return (gest_error_token(BAD_TOK, "`<<<'\n", 2), 0);
	else if (chevron_count == 1)
		return (gest_error_token(BAD_TOK, "`<'\n", 2), 0);
	else
		return (1);
}

int	single_heredoc_start_message(int count)
{
	if (count == 4)
		return (gest_error_token(BAD_TOK, "`<'\n", 2), 0);
	else if (count == 5)
		return (gest_error_token(BAD_TOK, "`<<'\n", 2), 0);
	else if (count >= 6)
		return (gest_error_token(BAD_TOK, "`<<<'\n", 2), 0);
	return (1);
}

int	multiple_heredoc_start_message(int chevron_count)
{
	if (chevron_count == 1)
		return (gest_error_token(BAD_TOK, "`<'\n", 2), 0);
	else if (chevron_count == 2)
		return (gest_error_token(BAD_TOK, "`<<'\n", 2), 0);
	else if (chevron_count >= 3)
		return (gest_error_token(BAD_TOK, "`<<<'\n", 2), 0);
	else
		return (1);
}
