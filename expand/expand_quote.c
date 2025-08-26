/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:40:05 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/16 16:39:00 by amdevezi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	should_copy_char(char c, int in_single, int in_double)
{
	if ((c == '\'' && !in_double) || (c == '\"' && !in_single))
		return (0);
	return (1);
}

char	*remove_quotes(char *str)
{
	char	*res;
	int		i;
	int		j;
	int		in_single;
	int		in_double;

	i = 0;
	j = 0;
	in_single = 0;
	in_double = 0;
	if (!str)
		return (NULL);
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		update_quotes(str[i], &in_single, &in_double);
		if (should_copy_char(str[i], in_single, in_double))
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	free(str);
	return (res);
}

void	update_quotes(char c, int *in_single, int *in_double)
{
	if (c == '\'' && !(*in_double))
		*in_single = !(*in_single);
	else if (c == '\"' && !(*in_single))
		*in_double = !(*in_double);
}

void	update_quote_state(char c, int *singleq, int *doubleq)
{
	if (c == '\'' && !(*doubleq))
		*singleq = !(*singleq);
	else if (c == '"' && !(*singleq))
		*doubleq = !(*doubleq);
}

char	*check_quote_and_copy(char *str, char *result, int count)
{
	char	*copy;

	if (count % 2 != 0)
	{
		free(result);
		return (NULL);
	}
	if (count == 0)
	{
		free(result);
		copy = malloc(ft_strlen(str) + 1);
		if (!copy)
			return (NULL);
		ft_strcpy(copy, str);
		return (copy);
	}
	return (result);
}
