/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:40:05 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/21 14:07:04 by amdevezi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_closing_quote(char *str, char last, int start)
{
	int	i;

	i = start;
	while (str[i])
	{
		if (str[i] == last)
			return (i);
		i++;
	}
	return (-1);
}

char	*extract_between(const char *str, int start, int end)
{
	int		len;
	char	*res;

	len = end - start;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, str + start, len + 1);
	return (res);
}

int	process_quote(char *str, int *i, char **result, int *quote_count)
{
	char	quote;
	int		start;
	int		end;
	char	*temp;
	char	*new_result;

	quote = str[*i];
	start = *i + 1;
	end = find_closing_quote(str, quote, start);
	if (end == -1)
		return (free(*result), *result = NULL, 0);
	*quote_count = *quote_count + 2;
	temp = extract_between(str, start, end);
	if (!temp)
		return (free(*result), *result = NULL, 0);
	new_result = join_and_free(*result, temp);
	if (!new_result)
		return (free(temp), free(*result), *result = NULL, 0);
	*result = new_result;
	free(temp);
	*i = end;
	return (1);
}

char	*extract_all_quotes(char *str)
{
	int		i;
	int		quote_count;
	char	*result;

	i = 0;
	quote_count = 0;
	result = malloc(1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	while (str[i])
	{
		if (is_quote(str[i]) == 1)
		{
			if (!process_quote(str, &i, &result, &quote_count))
			{
				free(result);
				return (NULL);
			}
		}
		i++;
	}
	return (check_quote_and_copy(str, result, quote_count));
}

int	check(char *text)
{
	char	*res;

	res = extract_all_quotes(text);
	if (res)
	{
		free(res);
		return (1);
	}
	else
	{
		gest_error("bad number of quotes\n", NULL, 2);
		return (0);
	}
}
