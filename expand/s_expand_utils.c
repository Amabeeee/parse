/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_expand_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 21:46:09 by lauraper          #+#    #+#             */
/*   Updated: 2025/08/17 00:37:45 by lauraper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*copy_quote(char *str, char c)
{
	int		i;
	char	*res;

	i = int_until_next_c(&(str[1]), c) + 2;
	res = malloc(sizeof(char) * (i + 1));
	i = 0;
	if (!res)
		return (NULL);
	if (str[i] == c)
	{
		res[i] = str[i];
		i++;
	}
	while (str[i] && str[i] != c)
	{
		res[i] = str[i];
		i++;
	}
	if (str[i] == c)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

char	*copy_until_next_quote(char *str)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	len = 0;
	res = NULL;
	while (str[len] && str[len] != '\"' && str[len] != '\'')
		len++;
	res = malloc(sizeof(char) * (len + 2));
	if (!res)
		return (NULL);
	while (str[i] && str[i] != '\"' && str[i] != '\'')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

static void	handle_quote(char c, int *single_quote, int *double_quote, int *res)
{
	if (c == '\'' && !*double_quote && !*single_quote)
	{
		*single_quote = 1;
		(*res)++;
	}
	else if (c == '\"' && !*single_quote && !*double_quote)
	{
		*double_quote = 1;
		(*res)++;
	}
	else if (c == '\'' && *single_quote)
		*single_quote = 0;
	else if (c == '\"' && *double_quote)
		*double_quote = 0;
}

int	count_quote_in_token(char *str)
{
	int	i;
	int	single_quote;
	int	doublequote;
	int	res;

	i = 0;
	res = 0;
	single_quote = 0;
	doublequote = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		handle_quote(str[i], &single_quote, &doublequote, &res);
		if (!single_quote && !doublequote && !is_quote(str[i]))
		{
			res++;
			while (str[i] && !is_quote(str[i]))
				i++;
		}
		else
			i++;
	}
	return (res);
}
