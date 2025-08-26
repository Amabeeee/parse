/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_out1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:15:11 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/14 19:32:32 by amdevezi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_trailing_token(const char *s)
{
	if (*s == '<')
		return (gest_error_token(BAD_TOK, "`<'\n", 2), 0);
	if (*s == '|')
		return (gest_error_token(BAD_TOK, "`|'\n", 2), 0);
	if (*s == '>')
		return (gest_error_token(BAD_TOK, "`>'\n", 2), 0);
	return (1);
}

int	check_out_start_error(const char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] != '>')
		return (1);
	while (s[i] == '>')
	{
		count++;
		i++;
	}
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (count == 1 && s[i] == '\0')
		return (gest_error_token(BAD_TOK, "`newline'\n", 2), 0);
	if (count >= 3)
		return (gest_error_token(BAD_TOK, "`>'\n", 2), 0);
	if (count == 1)
		return (check_trailing_token(&s[i]));
	return (1);
}

static int	check_following_chevrons(const char *s, int pos)
{
	int	next_count;

	next_count = count_chevrons(s, pos, '>');
	if (next_count >= 2)
		return (gest_error_token(BAD_TOK, "`>>'\n", 2), 0);
	if (next_count == 1)
		return (gest_error_token(BAD_TOK, "`>'\n", 2), 0);
	return (gest_error_token(BAD_TOK, "`>'\n", 2), 0);
}

int	check_out_middle_error(const char *s)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	while (s[i])
	{
		if (s[i] == '>')
		{
			count = count_chevrons(s, i, '>');
			j = i + count;
			while (ft_isspace(s[j]))
				j++;
			if (s[j] == '\0')
				return (1);
			if (s[j] == '>')
				return (check_following_chevrons(s, j));
			i = i + count;
		}
		else
			i++;
	}
	return (1);
}
