/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_out.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:49:23 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/09 21:26:52 by lauraper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_multiple_appends_start(const char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	while (s[i] == '>')
	{
		count++;
		i++;
	}
	if (count >= 3)
	{
		if (count == 3)
			return (gest_error_token(BAD_TOK, "'>'\n", 2), 0);
		else
			return (gest_error_token(BAD_TOK, "'>>'\n", 2), 0);
	}
	return (1);
}

int	check_multiple_appends_middle(const char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '>' && s[i + 1] == '>' && s[i + 2] == '>')
		{
			count = 3;
			i += 3;
			while (s[i] == '>')
			{
				count++;
				i++;
			}
			if (count == 3)
				return (gest_error_token(BAD_TOK, "'>'\n", 2), 0);
			else if (count > 3)
				return (gest_error_token(BAD_TOK, "'>>'\n", 2), 0);
		}
		else
			i++;
	}
	return (1);
}

int	check_multiple_appends_end(const char *s)
{
	int	len;
	int	i;
	int	count;

	len = ft_strlen(s);
	i = len - 1;
	while (i >= 0 && ft_isspace(s[i]))
		i--;
	count = 0;
	while (i >= 0 && s[i] == '>')
	{
		count++;
		i--;
	}
	if (count >= 3)
	{
		if (count == 3)
			return (gest_error_token(BAD_TOK, "'>'\n", 2), 0);
		else
			return (gest_error_token(BAD_TOK, "'>>'\n", 2), 0);
	}
	return (1);
}
