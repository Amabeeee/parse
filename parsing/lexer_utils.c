/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:57:29 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/16 13:40:00 by amdevezi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_remove_spaces(char *s)
{
	int		start;
	int		end;
	int		len;
	char	*res;

	start = 0;
	end = ft_strlen(s) - 1;
	while (s[start] == ' ')
		start++;
	while (end >= start && s[end] == ' ')
		end--;
	len = end - start + 1;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s + start, len + 1);
	return (res);
}

int	skip_quotes(const char *s, int i)
{
	char	quote;

	quote = s[i];
	i++;
	while (s[i] && s[i] != quote)
		i++;
	if (s[i] == quote)
		i++;
	return (i);
}

void	parse_char(t_parse *point)
{
	char	quote;

	if (point->s[point->i] == ' ')
	{
		add_token(point);
		while (point->s[point->i] == ' ')
			point->i++;
		point->start = point->i;
	}
	else if (is_quote(point->s[point->i]) == 1)
	{
		quote = point->s[point->i];
		point->i++;
		while (point->s[point->i] && point->s[point->i] != quote)
			point->i++;
		if (point->s[point->i] == quote)
			point->i++;
	}
	else if (is_separator(point->s[point->i]) == 1)
		token_limit(point);
	else
		point->i++;
}

int	handle_quotes(const char *str, int *i)
{
	if (is_quote(str[*i]) == 1)
	{
		*i = skip_quotes(str, *i);
		return (1);
	}
	return (0);
}
