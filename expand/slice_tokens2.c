/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice_tokens2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:16:44 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/20 18:40:53 by amdevezi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_unquoted_token(char **res, char *str, int i, int k)
{
	int	len;

	len = 0;
	res[k] = copy_until_next_quote(&(str[i]));
	len = ft_strlen(res[k]);
	i = i + len;
	return (i);
}

static int	handle_empty_token(char **res, int i, int k)
{
	res[k] = ft_strdup("");
	i = i + 1;
	return (i);
}

static int	handle_quote_token(char **res, char *str, int i, int k)
{
	int		len;
	char	quote;

	len = 0;
	quote = str[i];
	res[k] = copy_quote(&(str[i]), quote);
	len = int_until_next_c(&(str[i + 1]), quote);
	i = i + 2 + len;
	return (i);
}

static char	**fill_token_array(char **res, char *str)
{
	int	i;
	int	k;

	i = 0;
	k = -1;
	while (str[i])
	{
		k++;
		if (str[i] == '\"' || str[i] == '\'')
			i = handle_quote_token(res, str, i, k);
		else if (str[i + 1] == '\'' || str[i + 1] == '\"')
			i = handle_empty_token(res, i, k);
		else
			i = handle_unquoted_token(res, str, i, k);
		if (i > ft_strlen(str))
			break ;
	}
	res[k + 1] = NULL;
	return (res);
}

char	**slice_token(char *str)
{
	char	**res;
	int		count;

	res = NULL;
	count = 0;
	if (!str)
		return (NULL);
	count = count_quote_in_token(str) + 1;
	res = alloc_tokens_slice(sizeof(*res) * count);
	if (!res)
		return (NULL);
	return (fill_token_array(res, str));
}
