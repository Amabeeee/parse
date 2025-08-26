/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_token_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:57:29 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/09 17:38:23 by lauraper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token_limit(t_parse *point)
{
	add_token(point);
	if (handle_double_operator(point->tokens, point->s, point->i, &(point->j)))
		point->i = point->i + 2;
	else
	{
		handle_single_operator(point->tokens, point->s, point->i, &(point->j));
		point->i++;
	}
	point->start = point->i;
}

void	last_token(t_parse *point)
{
	char	*raw;

	if (point->i > point->start)
	{
		raw = ft_strndup(point->s + point->start, point->i - point->start);
		point->tokens[point->j] = ft_remove_spaces(raw);
		point->j++;
		free(raw);
	}
	point->tokens[point->j] = NULL;
}

int	count_tokens(const char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		i = skip_spaces(str, i);
		if (!str[i])
			break ;
		if (handle_quotes(str, &i))
			count++;
		else
			count = count + handle_operator_or_word(str, &i);
	}
	return (count);
}
