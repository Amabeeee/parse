/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:49:23 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/20 18:39:46 by amdevezi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_out_in_start_error(const char *s)
{
	int		i;

	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] == '>' || s[i] == '<')
	{
		i++;
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i] == '\0')
			return (gest_error_token(BAD_TOK, "`newline'\n", 2), 0);
	}
	return (1);
}

int	skip_spaces(const char *s, int i)
{
	while (s[i] && ft_isspace(s[i]))
		i++;
	return (i);
}
