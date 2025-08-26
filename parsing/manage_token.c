/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:57:29 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/09 17:25:36 by lauraper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_token(t_parse *point)
{
	if (point->i > point->start)
	{
		point->tokens[point->j]
			= ft_strndup(point->s + point->start, point->i - point->start);
		point->j++;
	}
}

char	**init_tokens(const char *s, int *number)
{
	char	**tokens;

	if (!s)
		return (NULL);
	*number = count_tokens(s);
	tokens = malloc(sizeof(char *) * (*number + 1));
	return (tokens);
}

char	**tokenize(const char *s)
{
	t_parse	point;
	int		number;

	point.i = 0;
	point.j = 0;
	point.start = 0;
	point.s = s;
	point.tokens = init_tokens(s, &number);
	if (!point.tokens)
		return (NULL);
	while (point.s[point.i])
		parse_char(&point);
	last_token(&point);
	point.tokens[point.j] = NULL;
	return (point.tokens);
}
