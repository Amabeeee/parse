/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:57:29 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/09 17:29:01 by lauraper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_double_operator(char **tokens, const char *s, int i, int *j)
{
	if ((s[i] == '<' || s[i] == '>') && s[i + 1] == s[i])
	{
		tokens[*j] = ft_strndup(s + i, 2);
		(*j)++;
		return (2);
	}
	return (0);
}

int	handle_single_operator(char **tokens, const char *s, int i, int *j)
{
	if (s[i] != ' ')
	{
		tokens[*j] = ft_strndup(s + i, 1);
		(*j)++;
		return (1);
	}
	return (0);
}

int	handle_operator_or_word(const char *str, int *i)
{
	if ((str[*i] == '<' || str[*i] == '>') && str[*i + 1] == str[*i])
	{
		*i = *i + 2;
		return (1);
	}
	else if (is_separator(str[*i]) == 1)
	{
		(*i)++;
		return (1);
	}
	else
	{
		while (str[*i] && !is_separator(str[*i]) && !is_quote(str[*i]))
			(*i)++;
		return (1);
	}
}

int	handle_operator(const char *s, int i, int *expect_operand)
{
	if ((s[i] == '<' || s[i] == '>') && s[i + 1] == s[i])
		i = i + 2;
	else
		i++;
	while (s[i] == ' ')
		i++;
	if (s[i] == '\0' || (is_operator(s[i]) == 1))
	{
		gest_error("erreur de syntaxe", NULL, 2);
		return (0);
	}
	*expect_operand = 1;
	return (i);
}
