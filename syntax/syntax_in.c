/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_in_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:49:23 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/15 14:25:53 by amdevezi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_in_start_error(const char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] == '<')
	{
		while (s[i] == '<')
		{
			count++;
			i++;
		}
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (count == 1 && s[i] == '\0')
			return (gest_error_token(BAD_TOK, "`newline'\n", 2), 0);
		if (count > 2)
			return (gest_error_token(BAD_TOK, "`<<'\n", 2), 0);
		if (count == 1 && (s[i] == '<' || s[i] == '|' || s[i] == '<'))
			return (gest_error_token(BAD_TOK, "`<'\n", 2), 0);
	}
	return (1);
}

int	handle_single_chevron_middle(const char *s, int i)
{
	int	j;
	int	next_count;

	j = i + 1;
	while (s[j] && ft_isspace(s[j]))
		j++;
	if (s[j] == '\0')
		return (1);
	if (s[j] == '<')
	{
		next_count = count_chevrons(s, j, '<');
		if (next_count >= 2)
			return (gest_error_token(BAD_TOK, "`<<'\n", 2), 0);
		else
			return (gest_error_token(BAD_TOK, "`<'\n", 2), 0);
	}
	return (1);
}

static int	process_chevron(const char *s, int *i_ptr)
{
	int	j;
	int	count;

	count = count_chevrons(s, *i_ptr, '<');
	j = *i_ptr + count;
	while (s[j] && ft_isspace(s[j]))
		j++;
	if (s[j] == '\0')
		return (1);
	if (count >= 2)
	{
		*i_ptr = *i_ptr + count;
		return (1);
	}
	if (count == 1)
	{
		if (handle_single_chevron_middle(s, *i_ptr) == 0)
			return (0);
		else if (!check_is_safe(&s[*i_ptr + count]))
			return (gest_error_token(BAD_TOK, "`newline'\n", 2), 0);
		*i_ptr = *i_ptr + count;
	}
	return (1);
}

int	check_in_middle_error(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '<')
		{
			if (process_chevron(s, &i) == 0)
				return (0);
		}
			i++;
	}
	return (1);
}
