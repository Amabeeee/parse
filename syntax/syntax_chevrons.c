/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_chevrons.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:49:23 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/09 21:16:53 by lauraper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_chevrons(const char *s, int j, char chevron)
{
	int	count;

	count = 0;
	while (s[j] == chevron)
	{
		count++;
		j++;
	}
	return (count);
}

int	report_chevron_error(int count, char chevron)
{
	if (chevron == '<')
	{
		if (count >= 3)
			return (gest_error_token(BAD_TOK, "`<<<'\n", 2), 0);
		if (count == 1)
			return (gest_error_token(BAD_TOK, "`<`\n", 2), 0);
	}
	else
	{
		if (count >= 3)
			return (gest_error_token(BAD_TOK, "`>>'\n", 2), 0);
		if (count == 2)
			return (gest_error_token(BAD_TOK, "`>>'\n", 2), 0);
		if (count == 1)
			return (gest_error_token(BAD_TOK, "`>'\n", 2), 0);
	}
	return (1);
}

int	find_last_non_space_chevron(const char *s)
{
	int	i;

	i = ft_strlen(s) - 1;
	while (i >= 0 && ft_isspace(s[i]))
		i--;
	if (i >= 0 && (s[i] == '<' || s[i] == '>'))
		return (i);
	return (-1);
}

int	count_consecutive_chevrons(const char *s, int i, char chevron)
{
	int	count;

	count = 0;
	while (i >= 0 && s[i] == chevron)
	{
		count++;
		i--;
	}
	return (count);
}

int	has_previous_chevron_sequence(const char *s, int i, char chevron)
{
	while (i >= 0 && ft_isspace(s[i]))
		i--;
	if (i >= 0 && s[i] == chevron)
		return (1);
	return (0);
}
