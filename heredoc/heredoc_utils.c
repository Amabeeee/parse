/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:27:11 by lauraper          #+#    #+#             */
/*   Updated: 2025/08/19 10:13:00 by amdevezi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*concate(char *res, char *line)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = malloc(sizeof(char) * (ft_strlen(res) + ft_strlen(line) + 2));
	if (!tmp)
		return (res);
	i = 0;
	j = 0;
	while (res[i])
	{
		tmp[i] = res[i];
		i++;
	}
	while (line[j])
	{
		tmp[i + j] = line[j];
		j++;
	}
	tmp[i + j] = '\n';
	tmp[i + j + 1] = 0;
	free(res);
	return (tmp);
}

int	count_quote(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			res++;
		i++;
	}
	return (res);
}
