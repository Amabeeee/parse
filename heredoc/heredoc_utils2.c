/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 15:11:19 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/16 15:11:22 by amdevezi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	should_skip_dollar_quote(const char *s, int i)
{
	return (s[i] == '$' && s[i + 1] && is_quote(s[i + 1]));
}

static int	is_double_dollar(const char *s, int i)
{
	return (s[i] == '$' && s[i + 1] == '$');
}

static int	copy_characters(char *res, const char *src, int *i, int *j)
{
	if (is_quote(src[*i]))
	{
		(*i)++;
	}
	else if (should_skip_dollar_quote(src, *i))
	{
		*i = *i + 2;
	}
	else if (is_double_dollar(src, *i))
	{
		res[*j] = src[*i];
		res[*j + 1] = src[*i + 1];
		*i += 2;
		*j += 2;
	}
	else
	{
		res[*j] = src[*i];
		(*i)++;
		(*j)++;
	}
	return (0);
}

char	*delete_quote(char *delimiter)
{
	int		i;
	int		j;
	int		count;
	char	*res;

	i = 0;
	j = 0;
	count = count_quote(delimiter);
	res = malloc(sizeof(char) * (ft_strlen(delimiter) - count + 1));
	if (!res)
		return (NULL);
	while (delimiter[i])
		copy_characters(res, delimiter, &i, &j);
	res[j] = '\0';
	return (res);
}
