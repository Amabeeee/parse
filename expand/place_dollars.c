/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_dollars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauraper <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:21:25 by lauraper          #+#    #+#             */
/*   Updated: 2025/08/14 17:57:19 by lauraper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	place_dollar(char next, char previous, int squote, int dquote)
{
	if (!ft_isalnum(next) && next != '?' \
	&& dquote == 1)
		return (31);
	else if (!ft_isalnum(next) && next != '?' \
	&& squote == 1)
		return (31);
	else if (!ft_isalnum(next) && next != '?' \
	&& squote == 0 && dquote == 0 && !is_quote(next))
		return (31);
	else if (previous == '\\')
		return (31);
	return ('$');
}

char	*keep_dollar(char *str)
{
	int		dquote;
	int		squote;
	int		i;

	dquote = 0;
	squote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' && dquote == 0)
			dquote = 1;
		else if (str[i] == '\'' && squote == 0)
			squote = 1;
		else if (str[i] == '\"' && dquote == 1)
			dquote = 0;
		else if (str[i] == '\'' && squote == 1)
			squote = 0;
		else if (str[i] == '$' && i >= 1)
			str[i] = place_dollar(str[i + 1], str[i - 1], squote, dquote);
		else if (str[i] == '$')
			str[i] = place_dollar(str[i + 1], 0, squote, dquote);
		i++;
	}
	return (str);
}

char	**replace_dollars(char **tokens)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tokens[i])
	{
		j = 0;
		while (tokens[i][j])
		{
			if (tokens[i][j] == 31)
				tokens[i][j] = '$';
			j++;
		}
		i++;
	}
	return (tokens);
}

char	*add_dollars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 31)
			str[i] = '$';
		i++;
	}
	return (str);
}

char	**concate_add_dollars(char **tokens)
{
	char	*concatened;
	char	**token_slice;
	char	**new;

	concatened = concate_blanck_tab(tokens);
	concatened = add_dollars(concatened);
	new = tokenize(concatened);
	token_slice = remove_quotes_tab(new);
	free(concatened);
	return (token_slice);
}
