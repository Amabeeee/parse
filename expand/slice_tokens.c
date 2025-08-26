/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 21:42:41 by lauraper          #+#    #+#             */
/*   Updated: 2025/08/16 16:13:57 by amdevezi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**alloc_tokens_slice(int len)
{
	char	**res;

	if (len == 0)
		return (NULL);
	res = malloc(sizeof(*res) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = NULL;
	return (res);
}

int	len_table_str(char **tab)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (tab[i])
	{
		len += ft_strlen(tab[i]);
		i++;
	}
	return (len);
}

char	*expand_concate_sliced(char **tokens, t_env **envp)
{
	int		i;
	char	*res;
	char	*tmp;

	i = 0;
	while (tokens[i])
	{
		tmp = expand_re(envp, tokens[i]);
		free(tokens[i]);
		tokens[i] = ft_strdup(tmp);
		free(tmp);
		i++;
	}
	res = malloc(sizeof(char) * (len_table_str(tokens) + 1));
	if (!res)
		return (NULL);
	ft_bzero(res, sizeof(char) * (len_table_str(tokens) + 1));
	i = 0;
	while (tokens[i])
	{
		res = ft_strcat(res, tokens[i]);
		i++;
	}
	return (res);
}
