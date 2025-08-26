/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lexing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:20:11 by lauraper          #+#    #+#             */
/*   Updated: 2025/08/20 18:40:27 by amdevezi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	not_blanck(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > 32 && str[i] < 126)
			return (1);
		i++;
	}
	return (0);
}

int	check_line(char *line)
{
	if (!not_blanck(line))
		return (0);
	if (!check(line))
		return (0);
	if (test_all(line) != 1)
		return (0);
	return (1);
}

int	pre_check(char *line)
{
	if (check_line(line) == 1)
		return (1);
	else
	{
		g_last_return = 2;
		return (0);
	}
}

char	*add_expand_sliced(char *str, t_env **envp, int sliced)
{
	char	*tmp;

	if (sliced)
	{
		tmp = expand_sliced(str, envp);
		free(str);
		return (tmp);
	}
	else
	{
		tmp = expand_re(envp, str);
		free(str);
		return (tmp);
	}
}

char	**check_and_tokenize(t_env **envp, char *line)
{
	char	**tokens;
	int		i;
	char	**res;

	i = 0;
	if (pre_check(line) != 1)
		return (NULL);
	tokens = get_tokens(line);
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "<<") == 0)
			i++;
		else if (is_in(tokens[i], '$') && count_quote_in_token(tokens[i]) > 2)
			tokens[i] = add_expand_sliced(tokens[i], envp, 1);
		else
			tokens[i] = add_expand_sliced(tokens[i], envp, 0);
		i++;
	}
	res = concate_add_dollars(tokens);
	ft_free(tokens);
	return (res);
}
